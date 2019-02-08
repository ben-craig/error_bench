#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller();
void callee();
void caller2(int amount);
void callee2(int amount);
extern thread_local error_struct tls_error_struct_var;
extern int global_int;
