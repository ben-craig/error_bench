#include "TimeLogger.h"
#include <sched.h>
#include <stdio.h>
#include <time.h>

TimeLogger::TimeLogger(uint32_t i) noexcept {
  iters = i;
  sched_yield(); // try to avoid time slicing in the middle of a run
  timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  start = t.tv_sec * 1000000000 + t.tv_nsec;
}

TimeLogger::~TimeLogger() {
  timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  uint64_t stop = t.tv_sec * 1000000000 + t.tv_nsec;

  double count = (double)(stop - start);
  printf("%.4f\n", count / iters);
}

void Setup() noexcept {}
