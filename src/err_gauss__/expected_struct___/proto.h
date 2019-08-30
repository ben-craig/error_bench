#pragma once
#include <common/expected.hpp>

struct error_struct {
  void *error = nullptr;
  void *domain = nullptr;
};

tl::expected<void, error_struct> caller0(bool do_err);
tl::expected<void, error_struct> caller1(bool do_err);
tl::expected<void, error_struct> caller2(bool do_err);
tl::expected<void, error_struct> caller3(bool do_err);
tl::expected<void, error_struct> caller4(bool do_err);
tl::expected<void, error_struct> caller5(bool do_err);
tl::expected<void, error_struct> caller6(bool do_err);
tl::expected<void, error_struct> caller7(bool do_err);
tl::expected<void, error_struct> caller8(bool do_err);
tl::expected<void, error_struct> caller9(bool do_err);
tl::expected<void, error_struct> caller10(bool do_err);
tl::expected<void, error_struct> caller11(bool do_err);
tl::expected<void, error_struct> caller12(bool do_err);
tl::expected<void, error_struct> caller13(bool do_err);
tl::expected<void, error_struct> caller14(bool do_err);
tl::expected<void, error_struct> caller15(bool do_err);
tl::expected<void, error_struct> callee(bool do_err);

extern int global_val;
