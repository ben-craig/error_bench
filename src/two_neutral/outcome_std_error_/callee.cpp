#include "proto.h"
#include <limits.h>

result<void> callee() {
  return outcome::success();
}
result<void> callee2(int amount) {
  global_int += amount;
  return outcome::success();
}
