#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
error_struct caller();
error_struct callee();
error_struct caller2(int amount);
error_struct callee2(int amount);
extern int global_int;
