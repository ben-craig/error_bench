#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
outcome::result<void, int> caller() {
  Dtor d;
  outcome::result<void, int> e = callee();
  if (!e)
    return e;
  global_int = 0;
  return e;
}

outcome::result<void, int> caller2(int amount) {
  Dtor d;
  outcome::result<void, int> e = callee2(amount);
  if (!e)
    return e;
  global_int += amount;
  return e;
}
