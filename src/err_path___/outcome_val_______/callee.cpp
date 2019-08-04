#include "proto.h"
#include <common/dtor.h>
#include <limits.h>

result<void, int> callee(bool do_err) {
  if(do_err)
  {
    return outcome::failure(1);
  }
  return outcome::success();
}
