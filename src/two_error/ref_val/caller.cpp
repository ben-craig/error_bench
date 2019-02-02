#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller(int &e) {
  Dtor d;
  callee(e);
  if (e)
    return;
  global_int = 0;
}

void caller2(int amount, int &e) {
  Dtor d;
  callee2(amount, e);
  if (e)
    return;
  global_int += amount;
}
