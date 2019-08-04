#pragma once
#include <common/expected.hpp>

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};
tl::expected<void, error_struct> caller(bool do_err, int depth);
tl::expected<void, error_struct> callee(bool do_err);
extern int global_int;
