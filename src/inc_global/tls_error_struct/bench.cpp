#include <common/TimeLogger.h>
#include "proto.h"

int main()
{
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller();
  }
  TimeLogger logger;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller();
  }
}
