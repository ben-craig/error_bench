#include "proto.h"
#include <common/TimeLogger.h>

int main() {
  int e = 0;
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller(e);
  }
  NOP_SLED;
  TimeLogger logger;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller(e);
  }
}
