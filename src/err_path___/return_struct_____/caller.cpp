#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
error_struct caller(int depth) {
  NOP_SLED_HEAD_2;
  Dtor d;
  error_struct e;
  if(depth == 1)
    e = callee();
  else
    e = caller(depth - 1);
  if (e.error)
    return e;
  global_int = 0;
  return e;
}
