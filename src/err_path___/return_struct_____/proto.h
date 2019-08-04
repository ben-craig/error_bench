#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
error_struct caller(bool do_err, int depth);
error_struct callee(bool do_err);
extern int global_int;
