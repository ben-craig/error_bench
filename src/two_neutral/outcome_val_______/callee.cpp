#include "proto.h"
#include <limits.h>

result<void, int> callee() {
  return outcome::success();
}
result<void, int> callee2(int amount) {
  global_int += amount;
  return outcome::success();
}
