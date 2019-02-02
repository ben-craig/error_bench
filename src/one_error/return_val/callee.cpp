#include "proto.h"
#include <limits.h>

int callee() {
  if (global_int == INT_MAX) {
    return 1;
  }
  return 0;
}
int callee2(int amount) {
  global_int += amount;
  return 0;
}
