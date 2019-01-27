#include <common/TimeLogger.h>
#include "proto.h"
#include <Windows.h>

int main()
{
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller();
    caller2(0);
  }
  TimeLogger logger(__FUNCTION__);
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller();
    caller2(0);
  }
}
