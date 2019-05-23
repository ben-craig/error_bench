#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller(error_struct &e) {
  Dtor d;
  callee(e);
  if (e.error)
    return;
  NOP_SLED_HEAD_2;
  global_int = 0;
}
