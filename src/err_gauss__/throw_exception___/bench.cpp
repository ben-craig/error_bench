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
  for (uint32_t i = 0; i < SLOW_WARMUP_ITERATIONS; ++i) {
    try { caller0(true); } catch(...) {}
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { caller0(true); } catch(...) {}
    }
    NOP_SLED_TAIL_B;
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
  for (uint32_t i = 0; i < SLOW_WARMUP_ITERATIONS; ++i) {
    try { param_caller0(&global_val, true); } catch(...) {}
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { param_caller0(&global_val, true); } catch(...) {}
    }
    NOP_SLED_TAIL_D;
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
  for (uint32_t i = 0; i < SLOW_WARMUP_ITERATIONS; ++i) {
    try { ret_caller0(true); } catch(...) {}
  }
  {
    TimeLogger logger(SLOW_ITERATIONS);
    NOP_SLED_HEAD_F;
    for (uint32_t i = 0; i < SLOW_ITERATIONS; ++i) {
      try { ret_caller0(true); } catch(...) {}
    }
    NOP_SLED_TAIL_F;
  }

}
