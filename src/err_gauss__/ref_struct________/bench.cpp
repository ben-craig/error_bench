#include "proto.h"
#include <common/TimeLogger.h>

int global_val = 0;

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)caller0(false, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_A;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)caller0(false, e);
    }
    NOP_SLED_TAIL_A;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)caller0(true, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)caller0(true, e);
    }
    NOP_SLED_TAIL_B;
  }

  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)param_caller0(&global_val, false, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)param_caller0(&global_val, false, e);
    }
    NOP_SLED_TAIL_C;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)param_caller0(&global_val, true, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)param_caller0(&global_val, true, e);
    }
    NOP_SLED_TAIL_D;
  }

  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)ret_caller0(false, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_E;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)ret_caller0(false, e);
    }
    NOP_SLED_TAIL_E;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    error_struct e;
    (void)ret_caller0(true, e);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_F;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      error_struct e;
      (void)ret_caller0(true, e);
    }
    NOP_SLED_TAIL_F;
  }
}
