#pragma once
#include <common/outcome.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

outcome::result<void, int> caller();
outcome::result<void, int> callee();
outcome::result<void, int> caller2(int amount);
outcome::result<void, int> callee2(int amount);
extern int global_int;
