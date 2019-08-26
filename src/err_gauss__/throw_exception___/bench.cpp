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
  for (uint32_t i = 0; i < SLOW_WARMUP_ITERATIONS; ++i) {
    try { caller15(true); } catch(...) {}
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller15(true); } catch(...) {}
    }
    NOP_SLED_TAIL_C;
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller0(true); } catch(...) {}
    }
    NOP_SLED_TAIL_D;
  }
}
