#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
result<void, error_struct> caller(int depth) {
  NOP_SLED_HEAD_2;
  Dtor d;
  if(depth == 1)
    OUTCOME_TRYV(callee());
  else
    OUTCOME_TRYV(caller(depth - 1));

  global_int = 0;
  return outcome::success();
}
