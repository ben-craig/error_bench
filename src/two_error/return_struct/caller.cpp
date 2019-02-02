#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
error_struct caller() {
  Dtor d;
  error_struct e = callee();
  if (e.error)
    return e;
  ++global_int;
  return e;
}

error_struct caller2(int amount) {
  Dtor d;
  error_struct e = callee2(amount);
  if (e.error)
    return e;
  global_int += amount;
  return e;
}
