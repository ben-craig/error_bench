#include "proto.h"
#include <common/TimeLogger.h>

int global_val = 0;

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)caller15(false, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_A;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)caller15(false, e);
    }
    NOP_SLED_TAIL_A;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)caller0(false, e);
    }
    NOP_SLED_TAIL_B;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)caller15(true, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)caller15(true, e);
    }
    NOP_SLED_TAIL_C;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)caller0(true, e);
    }
    NOP_SLED_TAIL_D;
  }
}
