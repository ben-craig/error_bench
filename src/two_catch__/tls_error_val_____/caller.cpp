#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller() {
  Dtor d;
  callee();
  if (tls_error_val_var)
    return;
  global_int = 0;
}

void caller2(int amount) {
  Dtor d;
  callee2(amount);
  if (tls_error_val_var)
    return;
  global_int += amount;
}
