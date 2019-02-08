#include "proto.h"
#include <limits.h>
#include <stdlib.h>

void callee() noexcept {
  if (global_int == INT_MAX)
    abort();
}
void callee2(int amount) noexcept { global_int += amount; }
