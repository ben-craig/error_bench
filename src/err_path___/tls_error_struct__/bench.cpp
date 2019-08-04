#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    tls_error_struct_var = {};
    caller(false, 1);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(false, 1);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(false, 16);
    }
    NOP_SLED_TAIL_1;
  }
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    tls_error_struct_var = {};
    caller(true, 1);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(true, 1);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(true, 16);
    }
    NOP_SLED_TAIL_1;
  }
}
