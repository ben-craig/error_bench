#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
tl::expected<void, error_struct> caller() {
  Dtor d;
  tl::expected<void, error_struct> e = callee();
  if (!e)
    return e;
  global_int = 0;
  return e;
}

tl::expected<void, error_struct> caller2(int amount) {
  Dtor d;
  tl::expected<void, error_struct> e = callee2(amount);
  if (!e)
    return e;
  global_int += amount;
  return e;
}
