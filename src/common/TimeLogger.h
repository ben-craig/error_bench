#pragma once
//#include <intrin.h>
#include <stdint.h>
#include "dtor.h"
static constexpr uint64_t ITERATIONS = 1ULL << 10;
static constexpr uint64_t WARMUP_ITERATIONS = 1ULL << 20;

struct TimeLogger {
  uint64_t start;
  TimeLogger() noexcept;
  ~TimeLogger();
};

void Setup() noexcept;
