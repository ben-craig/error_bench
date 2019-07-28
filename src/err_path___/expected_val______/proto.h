#pragma once
#include <common/expected.hpp>

tl::expected<void, int> caller(int depth);
tl::expected<void, int> callee();
extern int global_int;
