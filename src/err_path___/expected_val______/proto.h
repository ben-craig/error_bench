#pragma once
#include <common/expected.hpp>

tl::expected<void, int> caller(bool do_err, int depth);
tl::expected<void, int> callee(bool do_err);
extern int global_int;
