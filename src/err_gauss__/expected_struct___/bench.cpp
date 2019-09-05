#include "proto.h"
#include <common/TimeLogger.h>

int global_val = 0;

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)caller0(false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_A;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)caller0(false);
    }
    NOP_SLED_TAIL_A;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)caller1(false);
    }
    NOP_SLED_TAIL_B;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)caller0(true);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)caller0(true);
    }
    NOP_SLED_TAIL_C;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)caller1(true);
    }
    NOP_SLED_TAIL_D;
  }
}
