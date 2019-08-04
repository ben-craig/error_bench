#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller(bool do_err, int depth);
void callee(bool do_err);
extern thread_local error_struct tls_error_struct_var;
extern int global_int;
