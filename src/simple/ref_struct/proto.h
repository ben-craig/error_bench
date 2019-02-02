#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
void caller(error_struct &e);
void callee(error_struct &e);
