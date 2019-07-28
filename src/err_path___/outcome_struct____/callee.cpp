#include "proto.h"
#include <common/dtor.h>
#include <limits.h>

int error_info = 1;
int error_domain = 99;

result<void, error_struct> callee() {
  NOP_SLED_TAIL_2;
  return outcome::success();
}
