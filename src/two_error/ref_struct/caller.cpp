#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller(error_struct &e) {
  Dtor d;
  callee(e);
  if (e.error)
    return;
  ++global_int;
}

void caller2(int amount, error_struct &e) {
  Dtor d;
  callee2(amount, e);
  if (e.error)
    return;
  global_int += amount;
}
