#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    caller(false, 1, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      caller(false, 1, e);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      caller(false, 16, e);
    }
    NOP_SLED_TAIL_1;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    caller(true, 1, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      caller(true, 1, e);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      caller(true, 16, e);
    }
    NOP_SLED_TAIL_1;
  }
}
