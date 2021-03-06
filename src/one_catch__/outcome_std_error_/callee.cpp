#include "proto.h"
#include <limits.h>

result<void> callee() {
  if (global_int == INT_MAX) {
    return outcome::experimental::errc::argument_out_of_domain;
  }
  return outcome::success();
}
result<void> callee2(int amount) {
  if (global_int + amount == INT_MAX) {
    return outcome::experimental::errc::argument_out_of_domain;
  }
  global_int += amount;
  return outcome::success();
}
