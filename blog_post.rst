Error handling is never free.  In C++, you always pay some cost in order to react to an error condition.  It may be a speed cost from checks spread everywhere, or it may be a size cost for error handling cost, but costs are inevitable.

tl;dr: Exceptions are big, `std::abort` and integer error codes are small, and `expected` is somewhere in between.

You may think you can avoid all the costs by calling `std::abort` or something similar, but even that has costs.  The only cost-free option is to ignore the errors entirely and expose yourself to the wrath of UB.

So great, there are costs, but how should we measure the costs, and which error handling mechanisms exhibit what kinds of costs?

In this post, I will look at the *size* costs of error handling.  We'll break things down into one-time costs and incremental costs, and subdivide by costs paid for error neutral functions, raising an error, and handling an error.

To start with, we will look at code similar to the following:

```
struct Dtor {~Dtor() {}};

int global_int = 0;

void callee() {/* will raise an error one day*/}

void caller() {
  Dtor d;
  callee();
  global_int = 0;
}

int main() { 
  caller();
  return global_int;
}
```

This code has some important properties for future comparisons.
* `callee()` will eventually raise errors.
* `caller()` needs to clean up the `d` object in error and non-error conditions.
* `caller()` should only set `global_int` in success cases.
* The code doesn't have any error cases yet.  So we can see the cost of error handling machinery when no errors are involved.
In the actual tests all the function bodies are in separate .cpp files, and link-time / whole-program optimizations aren't used.  If they had been used, the entire program would get optimized away, removing our ability to measure error handling differences.

The above program is a useful template when using exceptions or `std::abort` as an error handling mechanism, but it won't work as well for error codes.  So we mutate the program like so...

```
int callee() {return 0;}

int caller() {
  Dtor d;
  int e = callee();
  if (e)
    return e;
  global_int = 0;
  return e;
}
```

This is pretty typical integer return value code, without some typical macro niceties.

In the interest of space, I will omit code for the other types of error handling, but I will describe all the strategies I tested here.  Most of the programs were built with exceptions turned off, but the throw_* cases and noexcept_terminate all had exceptions turned on in the program.
* terminate: When an error is encountered, kill the program.  Despite the name of the case, I used `std::abort` to kill the program.
* noexcept_terminate: Same as terminate, except exceptions are turned on, and all the functions I declare and define are marked as `noexcept`.
* return_struct: Return an `error_struct` object (described below) rather than an integer error code.
* ref_val and ref_struct: Rather than returning integers and `error_struct`s, construct them in main and pass them in by mutable reference.
* expected_val and expected_struct: Use tl::expected wrapping either an integer or an error_struct, accordingly.
* tls_val and tls_struct: Use thread_local variables to communicate error conditions.
* throw_val and throw_struct: Throw an integer or error_struct as an exception.  This is to allow a direct comparison to the other error handling strategies in terms of information transmitted from error site to handling site.
* throw_exception: Throw an exception deriving from std::exception, that contains only an int.  This should represent more typical use cases.

And here are the structures and classes necessary for the above:
```
struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};

class err_exception : public std::exception {
public:
  int val;
  explicit err_exception(int e) : val(e) {}
  const char *what() const noexcept override { return ""; }
};
```

Now for a few notes about my measuring methodology.  All the binaries are built with static runtimes, so that we can also see the cost of the exception handling runtime machinery.  For many people, this is a sunk cost.  If you are one of those people, don't pay attention to the one-time costs, and just look at the incremental costs.  Also, I didn't just do the "easy" thing and compare the on-disk sizes of the resulting programs.  Programs have lots and lots of padding internal to them due to alignment constraints, and that padding can mask or inflate small cost changes.  So instead, I measure the size by summing the size of all the non-code sections, and by summing the size of each function in the code sections.  Measuring the size of a function is a little tricky, as the compiler doesn't emit that information directly.  There are often padding instructions between consecutive functions.  My measurements omit the padding instructions so that we can see code size differences as small as one byte.

I also have measurements where I don't count the size of some data sections related to unwinding.  On x64 Linux, programs can have an .eh_frame and .eh_frame_hdr section that can help with emitting back traces.  x64 Windows has similar sections named .xdata and .pdata.  These sections aren't sufficient to implement C++ exception handling, and they don't go away when you turn off exceptions.  On Linux and Windows, these sections should be considered a sunk cost, but on more exotic platforms, it is reasonable to omit those sections, as you may not want to pay the cost to support a stack trace.  These measurements are all labeled as stripped.*.  x86 Windows doesn't have these sections, so the stripped.* measurements are the same as the unstripped measurements.

My first batch of measurements is comparing each of the mechanisms to the terminate test case that has no unwind information.  This lets us focus on the incremental costs of the other mechanisms.

```insert numeric CmpTerm table here```

So these tables show us that the one-time cost for exceptions is really high (6KB on MSVC x86, 384KB on Clang x64), and the one time cost for unwind information is pretty high too (6KB on MSVC x64, 57KB on Clang).  Once we ignore unwind information, we can see that the one-time cost for TLS on Windows is small compared to unwind information, but high compared to the other error mechanisms (196 bytes - 497 bytes).  All the other one-time overheads are 77 bytes or less.  Remember that this code doesn't currently have and throw statements in the program.  This is the one-time cost of error neutral functions when exceptions are turned on.

Note that noexcept_terminate has the same cost as regular terminate right now.  If everything is `noexcept`, you don't pay for the exception machinery.

Now, to measure the incremental cost of error neutral functions.  I'll update the code to add the following:

```
void callee2(int amount) {
  global_int += amount;
  // will error one day
}

void caller2(int amount) {
  Dtor d;
  callee2(amount);
  global_int += amount;
}

int main() { 
  caller();
  caller2(0);
  return global_int;
}
```

The "2" versions of these functions are slightly different than the original versions in order to avoid optimization where identical code is de-duplicated (COMDAT folding).  I updated each error handling case to the idiomatic form that had the same semantics as this error neutral form.  Here are the incremental numbers:

``` Insert Cost2ndNeutral values and graph ```

The delta between the best and the worst is much smaller in the incremental error neutral measurements than in the one-time cost measurements.  The largest incremental cost is GCC/x64 expected_struct (178 bytes), and the smallest is a tie between GCC/x64 and Clang/x64 stripped.terminate with 48 bytes.  There are many spurs in these graphs, and many of them can be attributed to codegen that is either low quality, or just code that isn't trying to be as small as possible.  Many of the struct cases resulted in the compiler generating vectorization code, which is almost always larger than the equivalent scalar code.  All of the exception cases had higher incremental costs than all of the stripped cases.  Terminate and return values were always cheaper than exceptions as well, even with included unwind information.

So what happens when you actually signal an error the first time?  What's the one-time cost of that first error?

```
void callee() {
  if (global_int == INT_MAX)
    throw 1;
}
```

``` Insert Cost1stError values and graph ```

On MSVC, there are multiple ways to build with exceptions "on".  I built with `/EHs`, which turns on exceptions in a C++ conforming manner.  The Microsoft recommended flag is `/EHsc`, which turns on exceptions for all C++ functions, but assumes that `extern "C"` functions won't throw.  This is a useful, though non-conforming option.  The trick is that the noexcept_terminate `callee()` implementation calls `abort()`, and that's an `extern "C"` function that isn't marked as `noexcept`, so we suddenly need to pay for all the exception handling costs that we had been avoiding by making everything `noexcept`.  We can't easily make the C runtime, or other people's code noexcept.  We don't see this on GCC and Clang because the C library they are calling marks abort as `[[noreturn]]` (TODO: check the spelling of this), and that lets them avoid generating the exception machinery.

