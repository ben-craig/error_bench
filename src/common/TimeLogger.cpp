#include "TimeLogger.h"
#include <Windows.h>
#include <stdio.h>

#if 1
TimeLogger::TimeLogger() noexcept {
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
#elif 0
  
HANDLE g_process;
FILETIME g_creation;
FILETIME g_exit;
FILETIME g_kernel;
FILETIME g_user;
FILETIME g2_creation;
FILETIME g2_exit;
FILETIME g2_kernel;
FILETIME g2_user;
TimeLogger::TimeLogger() noexcept {
  g_process = GetCurrentProcess();
  if(!GetProcessTimes(
    g_process,
    &g_creation,
    &g_exit,
    &g_kernel,
    &g_user))
  {
    exit(1);
  }
}

static double diffAsDouble(const FILETIME &e, const FILETIME &s)
{
  ULARGE_INTEGER end;
  end.HighPart = e.dwHighDateTime;
  end.LowPart = e.dwLowDateTime;

  ULARGE_INTEGER start;
  start.HighPart = s.dwHighDateTime;
  start.LowPart = s.dwLowDateTime;
  return (double)(end.QuadPart - start.QuadPart);
}

TimeLogger::~TimeLogger() {
  if(!GetProcessTimes(
    g_process,
    &g2_creation,
    &g2_exit,
    &g2_kernel,
    &g2_user))
  {
    exit(1);
  }

  fprintf(stderr, "raw begin user: %d %d\n", (int)g_user.dwHighDateTime, (int)g_user.dwLowDateTime);
  fprintf(stderr, "raw end user: %d %d\n", (int)g2_user.dwHighDateTime, (int)g2_user.dwLowDateTime);
  fprintf(stderr, "raw begin kernel: %d %d\n", (int)g_kernel.dwHighDateTime, (int)g_kernel.dwLowDateTime);
  fprintf(stderr, "raw end kernel: %d %d\n", (int)g2_kernel.dwHighDateTime, (int)g2_kernel.dwLowDateTime);
  double count = diffAsDouble(g2_kernel, g_kernel);
  count = count / 100.0;
  fprintf(stderr, "kernel: %.4f\n", count / ITERATIONS);
  
  count = diffAsDouble(g2_user, g_user);
  count = count / 100.0;
  printf("%.4f\n", count / ITERATIONS);
}
#else
HANDLE g_thread;

TimeLogger::TimeLogger() noexcept {
  g_thread = GetCurrentThread();
  Sleep(0); // try to avoid time slicing in the middle of a run
  if(!QueryThreadCycleTime(
    g_thread,
    &start))
  {
    exit(1);
  }
}

TimeLogger::~TimeLogger() {
  uint64_t end;
  if(!QueryThreadCycleTime(
    g_thread,
    &end))
  {
    exit(1);
  }

  double count = (double)(end - start);
  printf("%.4f\n", count / ITERATIONS);
}
#endif

void Setup() noexcept {
  BOOL result = SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
  if (!result) {
    printf("error %d\n", (int)GetLastError());
    exit(1);
  }
}
