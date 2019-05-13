#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller() {
  {
    Dtor d;
    callee();
    if (tls_error_val_var)
      return;
    NOP_SLED_HEAD_2;
    global_int = 0;
  }
  NOP_SLED_TAIL_2;
}
