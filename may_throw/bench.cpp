#include <common/TimeLogger.h>
#include "proto.h"
#include <Windows.h>

int main()
{
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller();
  }
  MemoryBarrier();
  TimeLogger logger(__FUNCTION__);
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller();
  }
}
