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
