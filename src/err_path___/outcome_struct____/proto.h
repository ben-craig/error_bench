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
result<void, error_struct> caller(bool do_err, int depth);
result<void, error_struct> callee(bool do_err);
extern int global_int;
