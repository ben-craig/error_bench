#include "proto.h"

tl::expected<void, int> callee() { return {}; }
tl::expected<void, int> callee2(int amount) {
  global_int += amount;
  return {};
}
