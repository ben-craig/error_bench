#include "common/nop2.h"
#include "proto.h"
#include <exception>

class err_exception : public std::exception {
public:
  int val;
  explicit err_exception(int e) : val(e) {}
  const char *what() const noexcept override { return ""; }
};

void callee(bool do_err) {
  inline_nop_X X;
  if(do_err)
    throw err_exception(1);
}

void param_callee(int *val, bool do_err) {
  (void) val;
  inline_nop_X X;
  if(do_err)
    throw err_exception(1);
}

int ret_callee(bool do_err) {
  inline_nop_X X;
  if(do_err)
    throw err_exception(1);
  return 0;
}

