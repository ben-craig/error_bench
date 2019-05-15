#pragma once
//#include <intrin.h>
#include <stdint.h>
#include "dtor.h"
static constexpr uint32_t ITERATIONS = (1UL << 20);
static constexpr uint32_t WARMUP_ITERATIONS = (1UL << 20);

struct TimeLogger {
  uint64_t start;
  TimeLogger() noexcept;
  ~TimeLogger();
};

void Setup() noexcept;
