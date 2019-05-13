#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  error_struct e;
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller(e);
  }
  TimeLogger logger;
  NOP_SLED_HEAD_1;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller(e);
  }
  NOP_SLED_TAIL_1;
}
