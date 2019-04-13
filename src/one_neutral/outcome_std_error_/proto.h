#pragma once
#include <outcome/experimental/status_result.hpp>
#include <outcome/try.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T>
using result = outcome::experimental::status_result<T>;

result<void> caller();
result<void> callee();
extern int global_int;
