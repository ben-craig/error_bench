#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
result<void, error_struct> caller(bool do_err, int depth) {
  NOP_SLED_HEAD_2;
  Dtor d;
  if(depth == 1)
  {
    OUTCOME_TRYV(callee(do_err));
  }
  else
  {
    OUTCOME_TRYV(caller(do_err, depth - 1));
  }
  global_int = 0;
  return outcome::success();
}
