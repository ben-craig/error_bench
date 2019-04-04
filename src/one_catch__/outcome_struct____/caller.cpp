#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
outcome::result<void, error_struct> caller() {
  Dtor d;
  outcome::result<void, error_struct> e = callee();
  if (!e)
    return e;
  global_int = 0;
  return e;
}

outcome::result<void, error_struct> caller2(int amount) {
  Dtor d;
  outcome::result<void, error_struct> e = callee2(amount);
  if (!e)
    return e;
  global_int += amount;
  return e;
}
