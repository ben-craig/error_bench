#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
int caller() {
  Dtor d;
  int e = callee();
  if (e)
    return e;
  global_int = 0;
  return e;
}
