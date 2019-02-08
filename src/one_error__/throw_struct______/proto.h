#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller();
void callee();
void caller2(int amount);
void callee2(int amount);
extern int global_int;
