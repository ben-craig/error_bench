#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller0(bool do_err);
void caller1(bool do_err);
void caller2(bool do_err);
void caller3(bool do_err);
void caller4(bool do_err);
void caller5(bool do_err);
void caller6(bool do_err);
void caller7(bool do_err);
void caller8(bool do_err);
void caller9(bool do_err);
void caller10(bool do_err);
void caller11(bool do_err);
void caller12(bool do_err);
void caller13(bool do_err);
void caller14(bool do_err);
void caller15(bool do_err);
void callee(bool do_err);
extern int global_int;
