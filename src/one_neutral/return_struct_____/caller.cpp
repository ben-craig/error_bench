#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
error_struct caller() {
  {
    Dtor d;
    error_struct e = callee();
    if (e.error)
      return e;
    NOP_SLED_HEAD_2;
    global_int = 0;
  }
  NOP_SLED_TAIL_2;
  return {};
}
