#include "proto.h"
#include <common/dtor.h>
#include <limits.h>

result<void> callee() {
  NOP_SLED_TAIL_2;
  return outcome::success();
}
