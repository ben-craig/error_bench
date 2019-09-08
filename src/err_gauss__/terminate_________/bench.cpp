#include "proto.h"
#include <common/TimeLogger.h>

int global_val = 0;

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller0(false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_A;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller0(false);
    }
    NOP_SLED_TAIL_A;
  }
  {
    TimeLogger logger;
    // empty log to satisfy scripts
  }

  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    param_caller0(&global_val, false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      param_caller0(&global_val, false);
    }
    NOP_SLED_TAIL_C;
  }
  {
    TimeLogger logger;
    // empty log to satisfy scripts
  }

  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    ret_caller0(false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_E;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      ret_caller0(false);
    }
    NOP_SLED_TAIL_E;
  }
  {
    TimeLogger logger;
    // empty log to satisfy scripts
  }
}
