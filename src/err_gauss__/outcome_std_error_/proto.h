#pragma once
//#include <outcome/experimental/status_result.hpp>
//#include <outcome/try.hpp>
#include <common/outcome-experimental.hpp>

namespace outcome = OUTCOME_V2_NAMESPACE;

template <class T>
using result = outcome::experimental::status_result<T>;

result<void> caller0(bool do_err);
result<void> caller1(bool do_err);
result<void> caller2(bool do_err);
result<void> caller3(bool do_err);
result<void> caller4(bool do_err);
result<void> caller5(bool do_err);
result<void> caller6(bool do_err);
result<void> caller7(bool do_err);
result<void> caller8(bool do_err);
result<void> caller9(bool do_err);
result<void> caller10(bool do_err);
result<void> caller11(bool do_err);
result<void> caller12(bool do_err);
result<void> caller13(bool do_err);
result<void> caller14(bool do_err);
result<void> caller15(bool do_err);
result<void> callee(bool do_err);

extern int global_val;

result<void> param_caller0(int *val, bool do_err);
result<void> param_caller1(int *val, bool do_err);
result<void> param_caller2(int *val, bool do_err);
result<void> param_caller3(int *val, bool do_err);
result<void> param_caller4(int *val, bool do_err);
result<void> param_caller5(int *val, bool do_err);
result<void> param_caller6(int *val, bool do_err);
result<void> param_caller7(int *val, bool do_err);
result<void> param_caller8(int *val, bool do_err);
result<void> param_caller9(int *val, bool do_err);
result<void> param_caller10(int *val, bool do_err);
result<void> param_caller11(int *val, bool do_err);
result<void> param_caller12(int *val, bool do_err);
result<void> param_caller13(int *val, bool do_err);
result<void> param_caller14(int *val, bool do_err);
result<void> param_caller15(int *val, bool do_err);
result<void> param_callee(int *val, bool do_err);

result<int> ret_caller0(bool do_err);
result<int> ret_caller1(bool do_err);
result<int> ret_caller2(bool do_err);
result<int> ret_caller3(bool do_err);
result<int> ret_caller4(bool do_err);
result<int> ret_caller5(bool do_err);
result<int> ret_caller6(bool do_err);
result<int> ret_caller7(bool do_err);
result<int> ret_caller8(bool do_err);
result<int> ret_caller9(bool do_err);
result<int> ret_caller10(bool do_err);
result<int> ret_caller11(bool do_err);
result<int> ret_caller12(bool do_err);
result<int> ret_caller13(bool do_err);
result<int> ret_caller14(bool do_err);
result<int> ret_caller15(bool do_err);
result<int> ret_callee(bool do_err);

result<int> ret_nd_caller0(bool do_err);
result<int> ret_nd_caller1(bool do_err);
result<int> ret_nd_caller2(bool do_err);
result<int> ret_nd_caller3(bool do_err);
result<int> ret_nd_caller4(bool do_err);
result<int> ret_nd_caller5(bool do_err);
result<int> ret_nd_caller6(bool do_err);
result<int> ret_nd_caller7(bool do_err);
result<int> ret_nd_caller8(bool do_err);
result<int> ret_nd_caller9(bool do_err);
result<int> ret_nd_caller10(bool do_err);
result<int> ret_nd_caller11(bool do_err);
result<int> ret_nd_caller12(bool do_err);
result<int> ret_nd_caller13(bool do_err);
result<int> ret_nd_caller14(bool do_err);
result<int> ret_nd_caller15(bool do_err);
result<int> ret_nd_callee(bool do_err);
