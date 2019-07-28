#include "proto.h"
#include <common/dtor.h>
#include <limits.h>

result<void, int> callee() {
  return outcome::failure(1);
}
