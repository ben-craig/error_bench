#pragma once
#include <stdint.h>

static constexpr uint64_t ITERATIONS = 1ULL<<26;
static constexpr uint64_t WARMUP_ITERATIONS = 1ULL << 26;

struct TimeLogger
{
  const char* str;
  uint64_t start;
  TimeLogger(const char *the_case);
  ~TimeLogger();
};

void Setup();
