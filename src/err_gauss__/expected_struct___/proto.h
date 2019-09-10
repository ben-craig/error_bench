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

tl::expected<void, error_struct> param_caller0(int *val, bool do_err);
tl::expected<void, error_struct> param_caller1(int *val, bool do_err);
tl::expected<void, error_struct> param_caller2(int *val, bool do_err);
tl::expected<void, error_struct> param_caller3(int *val, bool do_err);
tl::expected<void, error_struct> param_caller4(int *val, bool do_err);
tl::expected<void, error_struct> param_caller5(int *val, bool do_err);
tl::expected<void, error_struct> param_caller6(int *val, bool do_err);
tl::expected<void, error_struct> param_caller7(int *val, bool do_err);
tl::expected<void, error_struct> param_caller8(int *val, bool do_err);
tl::expected<void, error_struct> param_caller9(int *val, bool do_err);
tl::expected<void, error_struct> param_caller10(int *val, bool do_err);
tl::expected<void, error_struct> param_caller11(int *val, bool do_err);
tl::expected<void, error_struct> param_caller12(int *val, bool do_err);
tl::expected<void, error_struct> param_caller13(int *val, bool do_err);
tl::expected<void, error_struct> param_caller14(int *val, bool do_err);
tl::expected<void, error_struct> param_caller15(int *val, bool do_err);
tl::expected<void, error_struct> param_callee(int *val, bool do_err);

tl::expected<int, error_struct> ret_caller0(bool do_err);
tl::expected<int, error_struct> ret_caller1(bool do_err);
tl::expected<int, error_struct> ret_caller2(bool do_err);
tl::expected<int, error_struct> ret_caller3(bool do_err);
tl::expected<int, error_struct> ret_caller4(bool do_err);
tl::expected<int, error_struct> ret_caller5(bool do_err);
tl::expected<int, error_struct> ret_caller6(bool do_err);
tl::expected<int, error_struct> ret_caller7(bool do_err);
tl::expected<int, error_struct> ret_caller8(bool do_err);
tl::expected<int, error_struct> ret_caller9(bool do_err);
tl::expected<int, error_struct> ret_caller10(bool do_err);
tl::expected<int, error_struct> ret_caller11(bool do_err);
tl::expected<int, error_struct> ret_caller12(bool do_err);
tl::expected<int, error_struct> ret_caller13(bool do_err);
tl::expected<int, error_struct> ret_caller14(bool do_err);
tl::expected<int, error_struct> ret_caller15(bool do_err);
tl::expected<int, error_struct> ret_callee(bool do_err);

tl::expected<int, error_struct> ret_nd_caller0(bool do_err);
tl::expected<int, error_struct> ret_nd_caller1(bool do_err);
tl::expected<int, error_struct> ret_nd_caller2(bool do_err);
tl::expected<int, error_struct> ret_nd_caller3(bool do_err);
tl::expected<int, error_struct> ret_nd_caller4(bool do_err);
tl::expected<int, error_struct> ret_nd_caller5(bool do_err);
tl::expected<int, error_struct> ret_nd_caller6(bool do_err);
tl::expected<int, error_struct> ret_nd_caller7(bool do_err);
tl::expected<int, error_struct> ret_nd_caller8(bool do_err);
tl::expected<int, error_struct> ret_nd_caller9(bool do_err);
tl::expected<int, error_struct> ret_nd_caller10(bool do_err);
tl::expected<int, error_struct> ret_nd_caller11(bool do_err);
tl::expected<int, error_struct> ret_nd_caller12(bool do_err);
tl::expected<int, error_struct> ret_nd_caller13(bool do_err);
tl::expected<int, error_struct> ret_nd_caller14(bool do_err);
tl::expected<int, error_struct> ret_nd_caller15(bool do_err);
tl::expected<int, error_struct> ret_nd_callee(bool do_err);

