#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)caller();
  }
  TimeLogger logger;
  NOP_SLED_HEAD_1;
  for (uint32_t i = 0; i < ITERATIONS; ++i) {
    (void)caller();
  }
  NOP_SLED_TAIL_1;
}
