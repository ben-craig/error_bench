#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller(int depth);
void callee();
extern int global_int;
