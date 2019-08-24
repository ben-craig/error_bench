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
  #if 0
  for (uint32_t i = 0; i < SLOW_WARMUP_ITERATIONS; ++i) {
    try { caller15(true, param); } catch(...) {}
  }
  #endif
  {
    TimeLogger logger(SLOW_ITERATIONS);
    #if 0
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller15(true, param); } catch(...) {}
    }
    NOP_SLED_TAIL_C;
    #endif
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    #if 0
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller0(true, param); } catch(...) {}
    }
    NOP_SLED_TAIL_D;
    #endif
  }
}
