#pragma once
#include <outcome/result.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
outcome::result<void, error_struct> caller();
outcome::result<void, error_struct> callee();
extern int global_int;
