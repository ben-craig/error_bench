#include <common/TimeLogger.h>
#include "proto.h"
#include <Windows.h>

int main()
{
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller();
  }
  NOP_SLED; TimeLogger logger;
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller();
  }
}
