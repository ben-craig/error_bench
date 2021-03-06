#pragma once
//#include <intrin.h>
#include <stdint.h>

static constexpr uint64_t ITERATIONS = 1ULL << 10;
static constexpr uint64_t WARMUP_ITERATIONS = 1ULL << 26;

struct TimeLogger {
  uint64_t start;
  TimeLogger();
  ~TimeLogger();
};

void Setup();

#define NOP_SLED

#if 0
#define NOP_COUNT 0

#ifndef NOP_COUNT
#error "Missing NOP_COUNT!"
#endif

#define CONDITIONAL_NOP(x)                                                     \
  if (x < NOP_COUNT)                                                           \
  __nop()
#define NOP_SLED                                                               \
  CONDITIONAL_NOP(0);                                                          \
  CONDITIONAL_NOP(1);                                                          \
  CONDITIONAL_NOP(2);                                                          \
  CONDITIONAL_NOP(3);                                                          \
  CONDITIONAL_NOP(4);                                                          \
  CONDITIONAL_NOP(5);                                                          \
  CONDITIONAL_NOP(6);                                                          \
  CONDITIONAL_NOP(7);                                                          \
  CONDITIONAL_NOP(8);                                                          \
  CONDITIONAL_NOP(9);                                                          \
  CONDITIONAL_NOP(10);                                                         \
  CONDITIONAL_NOP(11);                                                         \
  CONDITIONAL_NOP(12);                                                         \
  CONDITIONAL_NOP(13);                                                         \
  CONDITIONAL_NOP(14);                                                         \
  CONDITIONAL_NOP(15);                                                         \
  CONDITIONAL_NOP(16);                                                         \
  CONDITIONAL_NOP(17);                                                         \
  CONDITIONAL_NOP(18);                                                         \
  CONDITIONAL_NOP(19);                                                         \
  CONDITIONAL_NOP(20);                                                         \
  CONDITIONAL_NOP(21);                                                         \
  CONDITIONAL_NOP(22);                                                         \
  CONDITIONAL_NOP(23);                                                         \
  CONDITIONAL_NOP(24);                                                         \
  CONDITIONAL_NOP(25);                                                         \
  CONDITIONAL_NOP(26);                                                         \
  CONDITIONAL_NOP(27);                                                         \
  CONDITIONAL_NOP(28);                                                         \
  CONDITIONAL_NOP(29);                                                         \
  CONDITIONAL_NOP(30);                                                         \
  CONDITIONAL_NOP(31);                                                         \
  CONDITIONAL_NOP(32);                                                         \
  CONDITIONAL_NOP(33);                                                         \
  CONDITIONAL_NOP(34);                                                         \
  CONDITIONAL_NOP(35);                                                         \
  CONDITIONAL_NOP(36);                                                         \
  CONDITIONAL_NOP(37);                                                         \
  CONDITIONAL_NOP(38);                                                         \
  CONDITIONAL_NOP(39);                                                         \
  CONDITIONAL_NOP(40);                                                         \
  CONDITIONAL_NOP(41);                                                         \
  CONDITIONAL_NOP(42);                                                         \
  CONDITIONAL_NOP(43);                                                         \
  CONDITIONAL_NOP(44);                                                         \
  CONDITIONAL_NOP(45);                                                         \
  CONDITIONAL_NOP(46);                                                         \
  CONDITIONAL_NOP(47);                                                         \
  CONDITIONAL_NOP(48);                                                         \
  CONDITIONAL_NOP(49);                                                         \
  CONDITIONAL_NOP(50);                                                         \
  CONDITIONAL_NOP(51);                                                         \
  CONDITIONAL_NOP(52);                                                         \
  CONDITIONAL_NOP(53);                                                         \
  CONDITIONAL_NOP(54);                                                         \
  CONDITIONAL_NOP(55);                                                         \
  CONDITIONAL_NOP(56);                                                         \
  CONDITIONAL_NOP(57);                                                         \
  CONDITIONAL_NOP(58);                                                         \
  CONDITIONAL_NOP(59);                                                         \
  CONDITIONAL_NOP(60);                                                         \
  CONDITIONAL_NOP(61);                                                         \
  CONDITIONAL_NOP(62);                                                         \
  CONDITIONAL_NOP(63)
#endif
