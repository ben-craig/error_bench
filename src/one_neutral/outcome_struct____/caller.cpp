#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
result<void, error_struct> caller() {
  {
    Dtor d;
    OUTCOME_TRYV(callee());
    NOP_SLED_HEAD_2;
    global_int = 0;
  }
  NOP_SLED_TAIL_2;
  return outcome::success();
}
