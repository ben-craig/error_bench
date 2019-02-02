#include "proto.h"

tl::expected<void, error_struct> callee() { return {}; }
tl::expected<void, error_struct> callee2(int amount) {
  global_int += amount;
  return {};
}
