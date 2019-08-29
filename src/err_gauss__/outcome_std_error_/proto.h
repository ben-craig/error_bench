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
