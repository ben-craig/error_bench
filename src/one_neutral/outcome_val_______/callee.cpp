#include "proto.h"
#include <limits.h>

result<void, int> callee() {
  return outcome::success();
}
