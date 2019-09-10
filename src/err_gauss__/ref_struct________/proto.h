#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};

void caller0(bool do_err, error_struct &e);
void caller1(bool do_err, error_struct &e);
void caller2(bool do_err, error_struct &e);
void caller3(bool do_err, error_struct &e);
void caller4(bool do_err, error_struct &e);
void caller5(bool do_err, error_struct &e);
void caller6(bool do_err, error_struct &e);
void caller7(bool do_err, error_struct &e);
void caller8(bool do_err, error_struct &e);
void caller9(bool do_err, error_struct &e);
void caller10(bool do_err, error_struct &e);
void caller11(bool do_err, error_struct &e);
void caller12(bool do_err, error_struct &e);
void caller13(bool do_err, error_struct &e);
void caller14(bool do_err, error_struct &e);
void caller15(bool do_err, error_struct &e);
void callee(bool do_err, error_struct &e);

extern int global_val;

void param_caller0(int *val, bool do_err, error_struct &e);
void param_caller1(int *val, bool do_err, error_struct &e);
void param_caller2(int *val, bool do_err, error_struct &e);
void param_caller3(int *val, bool do_err, error_struct &e);
void param_caller4(int *val, bool do_err, error_struct &e);
void param_caller5(int *val, bool do_err, error_struct &e);
void param_caller6(int *val, bool do_err, error_struct &e);
void param_caller7(int *val, bool do_err, error_struct &e);
void param_caller8(int *val, bool do_err, error_struct &e);
void param_caller9(int *val, bool do_err, error_struct &e);
void param_caller10(int *val, bool do_err, error_struct &e);
void param_caller11(int *val, bool do_err, error_struct &e);
void param_caller12(int *val, bool do_err, error_struct &e);
void param_caller13(int *val, bool do_err, error_struct &e);
void param_caller14(int *val, bool do_err, error_struct &e);
void param_caller15(int *val, bool do_err, error_struct &e);
void param_callee(int *val, bool do_err, error_struct &e);

int ret_caller0(bool do_err, error_struct &e);
int ret_caller1(bool do_err, error_struct &e);
int ret_caller2(bool do_err, error_struct &e);
int ret_caller3(bool do_err, error_struct &e);
int ret_caller4(bool do_err, error_struct &e);
int ret_caller5(bool do_err, error_struct &e);
int ret_caller6(bool do_err, error_struct &e);
int ret_caller7(bool do_err, error_struct &e);
int ret_caller8(bool do_err, error_struct &e);
int ret_caller9(bool do_err, error_struct &e);
int ret_caller10(bool do_err, error_struct &e);
int ret_caller11(bool do_err, error_struct &e);
int ret_caller12(bool do_err, error_struct &e);
int ret_caller13(bool do_err, error_struct &e);
int ret_caller14(bool do_err, error_struct &e);
int ret_caller15(bool do_err, error_struct &e);
int ret_callee(bool do_err, error_struct &e);

int ret_nd_caller0(bool do_err, error_struct &e);
int ret_nd_caller1(bool do_err, error_struct &e);
int ret_nd_caller2(bool do_err, error_struct &e);
int ret_nd_caller3(bool do_err, error_struct &e);
int ret_nd_caller4(bool do_err, error_struct &e);
int ret_nd_caller5(bool do_err, error_struct &e);
int ret_nd_caller6(bool do_err, error_struct &e);
int ret_nd_caller7(bool do_err, error_struct &e);
int ret_nd_caller8(bool do_err, error_struct &e);
int ret_nd_caller9(bool do_err, error_struct &e);
int ret_nd_caller10(bool do_err, error_struct &e);
int ret_nd_caller11(bool do_err, error_struct &e);
int ret_nd_caller12(bool do_err, error_struct &e);
int ret_nd_caller13(bool do_err, error_struct &e);
int ret_nd_caller14(bool do_err, error_struct &e);
int ret_nd_caller15(bool do_err, error_struct &e);
int ret_nd_callee(bool do_err, error_struct &e);
