#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
tl::expected<void, error_struct> caller(bool do_err, int depth) {
  NOP_SLED_HEAD_2;
  Dtor d;
  tl::expected<void, error_struct> e;
  if(depth == 1)
    e = callee(do_err);
  else
    e = caller(do_err, depth - 1);

  if (!e)
    return e;
  global_int = 0;
  return e;
}
