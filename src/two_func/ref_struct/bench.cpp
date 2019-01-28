#include <common/TimeLogger.h>
#include "proto.h"

int main()
{
  Setup();
  error_struct e;
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller(e);
    caller2(0, e);
  }
  TimeLogger logger;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller(e);
    caller2(0, e);
  }
}
