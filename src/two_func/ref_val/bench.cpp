#include <common/TimeLogger.h>
#include "proto.h"
#include <Windows.h>

int main()
{
  int e = 0;
  Setup();
  for (uint64_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller(e);
    caller2(0, e);
  }
  TimeLogger logger(__FUNCTION__);
  for (uint64_t i = 0; i < ITERATIONS; ++i) {
    caller(e);
    caller2(0, e);
  }
}
