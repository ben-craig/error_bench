#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller() {
  Dtor d;
  callee();
  global_int = 0;
}

void caller2(int amount) {
  Dtor d;
  callee2(amount);
  global_int += amount;
}
