#include "proto.h"
#include <limits.h>

tl::expected<void, int> callee() {
  if (global_int == INT_MAX) {
    return tl::unexpected<int>{1};
  }
  return {};
}
tl::expected<void, int> callee2(int amount) {
  global_int += amount;
  return {};
}
