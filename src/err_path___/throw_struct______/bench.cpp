#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint32_t i = 0; i < SLOW_WARMUP_ITERATIONS; ++i) {
    try { caller(1); } catch(...) {}
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller(1); } catch(...) {}
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller(2); } catch(...) {}
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller(4); } catch(...) {}
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller(8); } catch(...) {}
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller(16); } catch(...) {}
    }
    NOP_SLED_TAIL_1;
  }
}
