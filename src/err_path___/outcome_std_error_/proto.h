#pragma once
#include <outcome/experimental/status_result.hpp>
#include <outcome/try.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T>
using result = outcome::experimental::status_result<T>;

result<void> caller(bool do_err, int depth);
result<void> callee(bool do_err);
extern int global_int;
