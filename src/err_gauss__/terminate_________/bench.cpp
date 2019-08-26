#include "proto.h"
#include <common/TimeLogger.h>

int global_val = 0;

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller15(false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_A;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller15(false);
    }
    NOP_SLED_TAIL_A;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller0(false);
    }
    NOP_SLED_TAIL_B;
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
