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
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)caller0(true);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)caller0(true);
    }
    NOP_SLED_TAIL_B;
  }

  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)param_caller0(&global_val, false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)param_caller0(&global_val, false);
    }
    NOP_SLED_TAIL_C;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)param_caller0(&global_val, true);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)param_caller0(&global_val, true);
    }
    NOP_SLED_TAIL_D;
  }

  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)ret_caller0(false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_E;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)ret_caller0(false);
    }
    NOP_SLED_TAIL_E;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)ret_caller0(true);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_F;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)ret_caller0(true);
    }
    NOP_SLED_TAIL_F;
  }

  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)ret_nd_caller0(false);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_G;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)ret_nd_caller0(false);
    }
    NOP_SLED_TAIL_G;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    (void)ret_nd_caller0(true);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_H;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      (void)ret_nd_caller0(true);
    }
    NOP_SLED_TAIL_H;
  }

}
