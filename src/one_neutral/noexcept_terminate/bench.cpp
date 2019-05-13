#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller();
  }
  TimeLogger logger;
  NOP_SLED_HEAD_1;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller();
  }
  NOP_SLED_TAIL_1;
}
