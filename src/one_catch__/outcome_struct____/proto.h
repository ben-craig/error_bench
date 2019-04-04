#pragma once
#include <common/outcome.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
outcome::result<void, error_struct> caller();
outcome::result<void, error_struct> callee();
outcome::result<void, error_struct> caller2(int amount);
outcome::result<void, error_struct> callee2(int amount);
extern int global_int;
