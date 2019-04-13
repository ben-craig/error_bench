#include "proto.h"
#include <limits.h>

int error_info = 1;
int error_domain = 99;

result<void, error_struct> callee() {
  return outcome::success();
}
