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
