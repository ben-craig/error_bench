#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller(bool do_err, int depth) {
  NOP_SLED_HEAD_2;
  Dtor d;
  if(depth == 1)
    callee(do_err);
  else
    caller(do_err, depth - 1);
  if (tls_error_struct_var.error)
    return;
  global_int = 0;
}
