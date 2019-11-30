#include "proto.h"
#include <common/TimeLogger.h>

#define MY_DEBUG 0
#if MY_DEBUG
#include <stdio.h>
#endif

int global_val = 0;

int main() {
  Setup();
#if MY_DEBUG
  global_val = 42;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller0(&&warmup0, false);
  warmup0:;
  }
#if MY_DEBUG
  if(global_val != 0)
  {
    printf("bad warmup0\n");
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_A;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller0(&&bench0, false);
    bench0:;
    }
    NOP_SLED_TAIL_A;
  }

#if MY_DEBUG
  global_val = 42;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    caller0(&&warmup1, true);
  warmup1:;
  }
#if MY_DEBUG
  if(global_val != 42)
  {
    printf("bad warmup1\n");
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_B;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      caller0(&&bench1, true);
    bench1:;
    }
    NOP_SLED_TAIL_B;
  }


#if MY_DEBUG
  global_val = 42;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    param_caller0(&&warmup2, &global_val, false);
  warmup2:;
  }
#if MY_DEBUG
  if(global_val != 0)
  {
    printf("bad warmup2\n");
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_C;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      param_caller0(&&bench2, &global_val, false);
    bench2:;
    }
    NOP_SLED_TAIL_C;
  }

#if MY_DEBUG
  global_val = 42;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
    param_caller0(&&warmup3, &global_val, true);
  warmup3:;
  }
#if MY_DEBUG
  if(global_val != 42)
  {
    printf("bad warmup3\n");
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_D;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      param_caller0(&&bench3, &global_val, true);
    bench3:;
    }
    NOP_SLED_TAIL_D;
  }


#if MY_DEBUG
  global_val = 0;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
#if MY_DEBUG
    global_val =
#endif
      ret_caller0(&&warmup4, false);
  warmup4:;
  }
#if MY_DEBUG
  if(global_val != 8)
  {
    printf("bad warmup4 %d\n", global_val);
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_E;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      ret_caller0(&&bench4, false);
    bench4:;
    }
    NOP_SLED_TAIL_E;
  }

#if MY_DEBUG
  global_val = 0;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
#if MY_DEBUG
    global_val =
#endif
      ret_caller0(&&warmup5, true);
  warmup5:;
  }
#if MY_DEBUG
  if(global_val != 0)
  {
    printf("bad warmup5 %d\n", global_val);
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_F;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      ret_caller0(&&bench5, true);
    bench5:;
    }
    NOP_SLED_TAIL_F;
  }


#if MY_DEBUG
  global_val = 0;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
#if MY_DEBUG
    global_val =
#endif
      ret_nd_caller0(&&warmup6, false);
  warmup6:;
  }
#if MY_DEBUG
  if(global_val != 8)
  {
    printf("bad warmup6 %d\n", global_val);
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_G;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      ret_nd_caller0(&&bench6, false);
    bench6:;
    }
    NOP_SLED_TAIL_G;
  }

#if MY_DEBUG
  global_val = 0;
#endif
  for (uint32_t i = 0; i < WARMUP_ITERATIONS; ++i) {
#if MY_DEBUG
    global_val =
#endif
      ret_nd_caller0(&&warmup7, true);
  warmup7:;
  }
#if MY_DEBUG
  if(global_val != 0)
  {
    printf("bad warmup7 %d\n", global_val);
    return -1;
  }
#endif

  {
    TimeLogger logger;
    NOP_SLED_HEAD_H;
    for (uint32_t i = 0; i < ITERATIONS; ++i) {
      ret_nd_caller0(&&bench7, true);
    bench7:;
    }
    NOP_SLED_TAIL_H;
  }
}
