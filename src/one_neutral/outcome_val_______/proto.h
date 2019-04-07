#pragma once
#include <outcome/result.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

outcome::result<void, int> caller();
outcome::result<void, int> callee();
extern int global_int;
