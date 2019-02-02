#pragma once

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
error_struct caller();
error_struct callee();
