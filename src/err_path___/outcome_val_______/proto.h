#pragma once
#include <outcome/experimental/status_result.hpp>
#include <outcome/try.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T, class E>
using result = outcome::experimental::status_result<T, E>;

result<void, int> caller(bool do_err, int depth);
result<void, int> callee(bool do_err);
extern int global_int;
