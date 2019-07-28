#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller(int depth);
void callee();
extern thread_local error_struct tls_error_struct_var;
extern int global_int;
