#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller() {
  Dtor d;
  callee();
  if (tls_error_struct_var.error)
    return;
  NOP_SLED_HEAD_2;
  global_int = 0;
}
