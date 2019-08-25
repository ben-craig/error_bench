#pragma once
#include "nop.h"

#define NOP_SLED_HEAD_X NOP_SLED_IMPL(NOP_COUNT_X)
#define NOP_SLED_TAIL_X NOP_SLED_IMPL(31 - NOP_COUNT_X)
#define NOP_SLED_HEAD_Y NOP_SLED_IMPL(NOP_COUNT_Y)
#define NOP_SLED_TAIL_Y NOP_SLED_IMPL(31 - NOP_COUNT_Y)
#define NOP_SLED_HEAD_Z NOP_SLED_IMPL(NOP_COUNT_Z)
#define NOP_SLED_TAIL_Z NOP_SLED_IMPL(31 - NOP_COUNT_Z)

struct inline_nop_X {
  inline inline_nop_X() {NOP_SLED_HEAD_X;}
  inline ~inline_nop_X() {NOP_SLED_TAIL_X;}
};
