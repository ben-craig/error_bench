#include "proto.h"
#include <limits.h>

result<void, int> callee() {
  if (global_int == INT_MAX) {
    return outcome::failure(1);
  }
  return outcome::success();
}
result<void, int> callee2(int amount) {
  if (global_int + amount == INT_MAX) {
    return outcome::failure(1);
  }
  global_int += amount;
  return outcome::success();
}
