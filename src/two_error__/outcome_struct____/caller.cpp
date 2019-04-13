#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
result<void, error_struct> caller() {
  Dtor d;
  OUTCOME_TRYV(callee());
  global_int = 0;
  return outcome::success();
}

result<void, error_struct> caller2(int amount) {
  Dtor d;
  OUTCOME_TRYV(callee2(amount));
  global_int += amount;
  return outcome::success();
}
