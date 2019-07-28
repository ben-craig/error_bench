#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
result<void, error_struct> caller(int depth) {
  NOP_SLED_HEAD_2;
  Dtor d;
  if(depth == 1)
  {
    result<void, error_struct> && (inner1) = callee();
    if(!(inner1).has_value())
      return OUTCOME_V2_NAMESPACE::try_operation_return_as(static_cast<decltype(inner1) &&>(inner1));
  }
  else
  {
    result<void, error_struct> && (inner2) = caller(depth - 1);
    if(!(inner2).has_value())
      return OUTCOME_V2_NAMESPACE::try_operation_return_as(static_cast<decltype(inner2) &&>(inner2));
  }
  global_int = 0;
  return outcome::success();
}
