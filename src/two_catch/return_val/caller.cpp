#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
int caller() {
  Dtor d;
  int e = callee();
  if (e)
    return e;
  ++global_int;
  return e;
}

int caller2(int amount) {
  Dtor d;
  int e = callee2(amount);
  if (e)
    return e;
  global_int += amount;
  return e;
}
