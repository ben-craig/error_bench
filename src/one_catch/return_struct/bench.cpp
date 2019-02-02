#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller();
    caller2(0);
  }
  NOP_SLED;
  TimeLogger logger;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller();
    caller2(0);
  }
}
