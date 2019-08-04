#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller(bool do_err, int depth, error_struct &e);
void callee(bool do_err, error_struct &e);
extern int global_int;
