#pragma once
#include <common/outcome-experimental.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T, class E>
using result = outcome::experimental::status_result<T, E>;

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
result<void, error_struct> caller();
result<void, error_struct> callee();
extern int global_int;
