#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
error_struct caller(int depth);
error_struct callee();
extern int global_int;
