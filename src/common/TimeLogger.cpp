#include "TimeLogger.h"
#include <Windows.h>
#include <stdio.h>

TimeLogger::TimeLogger() {
  Sleep(0); // try to avoid time slicing in the middle of a run
  LARGE_INTEGER local_start;
  QueryPerformanceCounter(&local_start);
  start = local_start.QuadPart;
}

TimeLogger::~TimeLogger() {
  LARGE_INTEGER stop;
  QueryPerformanceCounter(&stop);

  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);

  double count = (double)(stop.QuadPart - start);
  count = count * 1e9 / freq.QuadPart;
  printf("%.4f\n", count / ITERATIONS);
}

void Setup() {
  BOOL result = SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
  if (!result) {
    printf("error %d\n", (int)GetLastError());
    exit(1);
  }
}
