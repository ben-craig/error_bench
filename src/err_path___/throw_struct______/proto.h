#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller(bool do_err, int depth);
void callee(bool do_err);
extern int global_int;
