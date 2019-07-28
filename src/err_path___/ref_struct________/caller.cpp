#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller(int depth, error_struct &e) {
  NOP_SLED_HEAD_2;
  Dtor d;
  if(depth == 1)
    callee(e);
  else
    caller(depth - 1, e);
  if (e.error)
    return;
  global_int = 0;
}
