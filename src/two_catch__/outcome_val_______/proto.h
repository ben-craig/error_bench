#pragma once
#include <outcome/experimental/status_result.hpp>
#include <outcome/try.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T, class E>
using result = outcome::experimental::status_result<T, E>;

result<void, int> caller();
result<void, int> callee();
result<void, int> caller2(int amount);
result<void, int> callee2(int amount);
extern int global_int;
