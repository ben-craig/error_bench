#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
int caller(int depth) {
  NOP_SLED_HEAD_2;
  Dtor d;
  int e;
  if(depth == 1)
    e = callee();
  else
    e = caller(depth - 1);
  if (e)
    return e;
  global_int = 0;
  return 0;
}
