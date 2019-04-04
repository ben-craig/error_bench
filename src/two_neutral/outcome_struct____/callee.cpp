#include "proto.h"

outcome::result<void, error_struct> callee() { return outcome::success(); }
outcome::result<void, error_struct> callee2(int amount) {
  global_int += amount;
  return outcome::success();
}
