#pragma once
#include <stdint.h>

static constexpr uint64_t ITERATIONS = 1ULL<<10;
static constexpr uint64_t WARMUP_ITERATIONS = 1ULL << 26;

struct TimeLogger
{
  uint64_t start;
  TimeLogger();
  ~TimeLogger();
};

void Setup();
