#include "proto.h"
#include <common/dtor.h>

tl::expected<void, int> callee() {
  return tl::unexpected<int>{1};
}
