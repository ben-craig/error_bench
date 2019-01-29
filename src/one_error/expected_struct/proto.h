#pragma once
#include <common/expected.hpp>

struct error_struct
{
    void *error = nullptr;
    void *domain = nullptr;
};
tl::expected<void, error_struct> caller();
tl::expected<void, error_struct> callee();
tl::expected<void, error_struct> caller2(int amount);
tl::expected<void, error_struct> callee2(int amount);
extern int global_int;
