#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  int e = 0;
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
