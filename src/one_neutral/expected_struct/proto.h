#pragma once
#include <common/expected.hpp>

struct error_struct
{
    void *error = nullptr;
    void *domain = nullptr;
};
tl::expected<void, error_struct> caller();
tl::expected<void, error_struct> callee();
extern int global_int;
