#pragma once
//#include <intrin.h>
#include <stdint.h>
#include "dtor.h"
static constexpr uint32_t ITERATIONS = (1UL << 20);
static constexpr uint32_t WARMUP_ITERATIONS = (1UL << 20);
static constexpr uint32_t SLOW_ITERATIONS = (1UL << 16);
static constexpr uint32_t SLOW_WARMUP_ITERATIONS = (1UL << 10);

struct TimeLogger {
  uint64_t start;
  uint32_t iters;
  TimeLogger(uint32_t i = ITERATIONS) noexcept;
  ~TimeLogger();
};

void Setup() noexcept;
