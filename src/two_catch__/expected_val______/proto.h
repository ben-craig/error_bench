#pragma once
#include <common/expected.hpp>

tl::expected<void, int> caller();
tl::expected<void, int> callee();
tl::expected<void, int> caller2(int amount);
tl::expected<void, int> callee2(int amount);
extern int global_int;
