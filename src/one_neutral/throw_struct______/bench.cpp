#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller();
  }
  NOP_SLED;
  TimeLogger logger;
  for (uint32_t i = 0; i < ITERATIONS; ++i) {
    caller();
  }
}
