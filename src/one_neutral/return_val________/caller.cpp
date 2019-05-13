#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
int caller() {
  {
    Dtor d;
    int e = callee();
    if (e)
      return e;
    NOP_SLED_HEAD_2;
    global_int = 0;
  }
  NOP_SLED_TAIL_2;
  return 0;
}
