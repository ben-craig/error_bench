#include "proto.h"
#include <common/dtor.h>

int global_int = 1;
void caller() {
  Dtor d;
  int a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
  a0 = a1 = a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = 1;
  NOP_SLED_HEAD_2;
  for (int i = 0; i < global_int; i++) {
    a9 = a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
    callee();
    a0 = a1;
    a1 = a2;
    a2 = a3;
    a3 = a4;
    a4 = a5;
    a5 = a6;
    a6 = a7;
    a7 = a8;
    a8 = a9;
  }
  global_int = a0;
}
