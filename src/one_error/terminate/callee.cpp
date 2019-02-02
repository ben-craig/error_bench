#include "proto.h"
#include <limits.h>
#include <stdlib.h>

void callee() {
  if (global_int == INT_MAX)
    abort();
}
void callee2(int amount) { global_int += amount; }
