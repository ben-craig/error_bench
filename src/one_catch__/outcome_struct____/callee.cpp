#include "proto.h"
#include <limits.h>

int error_info = 1;
int error_domain = 99;

outcome::result<void, error_struct> callee() {
  if (global_int == INT_MAX) {
    error_struct e;
    e.error = &error_info;
    e.domain = &error_domain;
    return outcome::failure(e);
  }
  return outcome::success();
}

outcome::result<void, error_struct> callee2(int amount) {
  if (global_int + amount == INT_MAX) {
    error_struct e;
    e.error = &error_info;
    e.domain = &error_domain;
    return outcome::failure(e);
  }
  global_int += amount;
  return outcome::success();
}
