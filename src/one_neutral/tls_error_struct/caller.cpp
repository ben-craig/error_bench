#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller() {
  Dtor d;
  callee();
  if (tls_error_struct_var.error)
    return;
  global_int = 0;
}
