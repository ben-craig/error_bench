#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  Setup();
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    tls_error_struct_var = {};
    caller(1);
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(1);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(2);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(4);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(8);
    }
    NOP_SLED_TAIL_1;
  }
  {
    TimeLogger logger;
    NOP_SLED_HEAD_1;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      tls_error_struct_var = {};
      caller(16);
    }
    NOP_SLED_TAIL_1;
  }
}
