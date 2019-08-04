#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller(false, 1);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller(false, 1);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller(false, 16);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    // empty log to satisfy scripts
  }
  {
    TimeLogger logger;
    // empty log to satisfy scripts
  }
}
