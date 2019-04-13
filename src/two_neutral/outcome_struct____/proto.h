#pragma once
#include <outcome/experimental/status_result.hpp>
#include <outcome/try.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T, class E>
using result = outcome::experimental::status_result<T, E>;

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
result<void, error_struct> caller();
result<void, error_struct> callee();
result<void, error_struct> caller2(int amount);
result<void, error_struct> callee2(int amount);
extern int global_int;
