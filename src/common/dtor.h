#pragma once
#ifdef _MSC_VER
#include <intrin.h>
#endif

struct Dtor {
  ~Dtor();
};

#if 0 //ifndef NOP_COUNT_1

#define NOP_SLED_HEAD_1
#define NOP_SLED_TAIL_1
#define NOP_SLED_HEAD_2
#define NOP_SLED_TAIL_2

#else

#ifndef NOP_COUNT_1
#error "Missing NOP_COUNT_1!"
#endif
#ifndef NOP_COUNT_2
#error "Missing NOP_COUNT_2!"
#endif

#ifdef _MSC_VER
#define CONDITIONAL_NOP(x, limit) if ((x) < limit) __nop()
#else
#define CONDITIONAL_NOP(x, limit) if ((x) < limit) __asm__ __volatile__("nop")
#endif

#define NOP_SLED_IMPL(limit)                    \
  CONDITIONAL_NOP(0, limit);       \
  CONDITIONAL_NOP(1, limit);       \
  CONDITIONAL_NOP(2, limit);       \
  CONDITIONAL_NOP(3, limit);       \
  CONDITIONAL_NOP(4, limit);       \
  CONDITIONAL_NOP(5, limit);       \
  CONDITIONAL_NOP(6, limit);       \
  CONDITIONAL_NOP(7, limit);       \
  CONDITIONAL_NOP(8, limit);       \
  CONDITIONAL_NOP(9, limit);       \
  CONDITIONAL_NOP(10, limit);      \
  CONDITIONAL_NOP(11, limit);      \
  CONDITIONAL_NOP(12, limit);      \
  CONDITIONAL_NOP(13, limit);      \
  CONDITIONAL_NOP(14, limit);      \
  CONDITIONAL_NOP(15, limit);      \
  CONDITIONAL_NOP(16, limit);      \
  CONDITIONAL_NOP(17, limit);      \
  CONDITIONAL_NOP(18, limit);      \
  CONDITIONAL_NOP(19, limit);      \
  CONDITIONAL_NOP(20, limit);      \
  CONDITIONAL_NOP(21, limit);      \
  CONDITIONAL_NOP(22, limit);      \
  CONDITIONAL_NOP(23, limit);      \
  CONDITIONAL_NOP(24, limit);      \
  CONDITIONAL_NOP(25, limit);      \
  CONDITIONAL_NOP(26, limit);      \
  CONDITIONAL_NOP(27, limit);      \
  CONDITIONAL_NOP(28, limit);      \
  CONDITIONAL_NOP(29, limit);      \
  CONDITIONAL_NOP(30, limit);      \
  CONDITIONAL_NOP(31, limit)

#define NOP_SLED_HEAD_1 NOP_SLED_IMPL(NOP_COUNT_1)
#define NOP_SLED_TAIL_1 NOP_SLED_IMPL(31 - NOP_COUNT_1)
#define NOP_SLED_HEAD_2 NOP_SLED_IMPL(NOP_COUNT_2)
#define NOP_SLED_TAIL_2 NOP_SLED_IMPL(31 - NOP_COUNT_2)

#endif
