#include <common/TimeLogger.h>
#include "proto.h"

int main()
{
  int e = 0;
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller(e);
    caller2(0, e);
  }
  NOP_SLED; TimeLogger logger;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller(e);
    caller2(0, e);
  }
}
