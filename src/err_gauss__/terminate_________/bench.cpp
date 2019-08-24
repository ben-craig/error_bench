#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  int param = 0;
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller15(false, param);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_A;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller15(false, param);
    }
    NOP_SLED_TAIL_A;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller0(false, param);
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
