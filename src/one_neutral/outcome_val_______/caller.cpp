#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
result<void, int> caller() {
  Dtor d;
  OUTCOME_TRYV(callee());
  global_int = 0;
  return outcome::success();
}
