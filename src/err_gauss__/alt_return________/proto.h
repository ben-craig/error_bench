#pragma once

namespace {

template <typename T>
T hide_value(T t) {
  asm volatile ("" : "+r"/*bind as in out*/ (t) : );
  return t;
}

}


void caller0(void *ret, bool do_err);
void caller1(void *ret, bool do_err);
void caller2(void *ret, bool do_err);
void caller3(void *ret, bool do_err);
void caller4(void *ret, bool do_err);
void caller5(void *ret, bool do_err);
void caller6(void *ret, bool do_err);
void caller7(void *ret, bool do_err);
void caller8(void *ret, bool do_err);
void caller9(void *ret, bool do_err);
void caller10(void *ret, bool do_err);
void caller11(void *ret, bool do_err);
void caller12(void *ret, bool do_err);
void caller13(void *ret, bool do_err);
void caller14(void *ret, bool do_err);
void caller15(void *ret, bool do_err);
void callee(void *ret, bool do_err);

extern int global_val;

void param_caller0(void *ret, int *val, bool do_err);
void param_caller1(void *ret, int *val, bool do_err);
void param_caller2(void *ret, int *val, bool do_err);
void param_caller3(void *ret, int *val, bool do_err);
void param_caller4(void *ret, int *val, bool do_err);
void param_caller5(void *ret, int *val, bool do_err);
void param_caller6(void *ret, int *val, bool do_err);
void param_caller7(void *ret, int *val, bool do_err);
void param_caller8(void *ret, int *val, bool do_err);
void param_caller9(void *ret, int *val, bool do_err);
void param_caller10(void *ret, int *val, bool do_err);
void param_caller11(void *ret, int *val, bool do_err);
void param_caller12(void *ret, int *val, bool do_err);
void param_caller13(void *ret, int *val, bool do_err);
void param_caller14(void *ret, int *val, bool do_err);
void param_caller15(void *ret, int *val, bool do_err);
void param_callee(void *ret, int *val, bool do_err);

int ret_caller0(void *ret, bool do_err);
int ret_caller1(void *ret, bool do_err);
int ret_caller2(void *ret, bool do_err);
int ret_caller3(void *ret, bool do_err);
int ret_caller4(void *ret, bool do_err);
int ret_caller5(void *ret, bool do_err);
int ret_caller6(void *ret, bool do_err);
int ret_caller7(void *ret, bool do_err);
int ret_caller8(void *ret, bool do_err);
int ret_caller9(void *ret, bool do_err);
int ret_caller10(void *ret, bool do_err);
int ret_caller11(void *ret, bool do_err);
int ret_caller12(void *ret, bool do_err);
int ret_caller13(void *ret, bool do_err);
int ret_caller14(void *ret, bool do_err);
int ret_caller15(void *ret, bool do_err);
int ret_callee(void *ret, bool do_err);

int ret_nd_caller0(void *ret, bool do_err);
int ret_nd_caller1(void *ret, bool do_err);
int ret_nd_caller2(void *ret, bool do_err);
int ret_nd_caller3(void *ret, bool do_err);
int ret_nd_caller4(void *ret, bool do_err);
int ret_nd_caller5(void *ret, bool do_err);
int ret_nd_caller6(void *ret, bool do_err);
int ret_nd_caller7(void *ret, bool do_err);
int ret_nd_caller8(void *ret, bool do_err);
int ret_nd_caller9(void *ret, bool do_err);
int ret_nd_caller10(void *ret, bool do_err);
int ret_nd_caller11(void *ret, bool do_err);
int ret_nd_caller12(void *ret, bool do_err);
int ret_nd_caller13(void *ret, bool do_err);
int ret_nd_caller14(void *ret, bool do_err);
int ret_nd_caller15(void *ret, bool do_err);
int ret_nd_callee(void *ret, bool do_err);
