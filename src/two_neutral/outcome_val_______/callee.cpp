#include "proto.h"

outcome::result<void, int> callee() { return outcome::success(); }
outcome::result<void, int> callee2(int amount) {
  global_int += amount;
  return outcome::success();
}
