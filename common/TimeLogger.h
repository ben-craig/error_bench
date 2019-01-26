#pragma once
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

static constexpr uint64_t ITERATIONS = 1ULL<<26;
static constexpr uint64_t WARMUP_ITERATIONS = 1ULL << 26;

struct TimeLogger
{
  const char* str;
  LARGE_INTEGER start;
  TimeLogger(const char *the_case);
  ~TimeLogger();
};

inline TimeLogger::TimeLogger(const char *the_case) :
  str(the_case)
{
  Sleep(0);  //try to avoid time slicing in the middle of a run
  QueryPerformanceCounter(&start);
}

inline TimeLogger::~TimeLogger()
{
  LARGE_INTEGER stop;
  QueryPerformanceCounter(&stop);

  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);

  double count = (double)(stop.QuadPart - start.QuadPart);
  count = count * 1e9 / freq.QuadPart;
  printf("%.4f\n", count / ITERATIONS);
}

inline void Setup()
{
  BOOL result = SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
  if (!result)
  {
      printf("error %d\n", (int)GetLastError());
      exit(1);
  }
}
