#pragma once
#include <common/outcome-experimental.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T, class E>
using result = outcome::experimental::status_result<T, E>;

result<void, int> caller();
result<void, int> callee();
extern int global_int;
