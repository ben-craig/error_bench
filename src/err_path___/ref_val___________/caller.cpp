#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller(int &e) {
  Dtor d;
  callee(e);
  if (e)
    return;
  NOP_SLED_HEAD_2;
  global_int = 0;
}
