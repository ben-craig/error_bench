#include "proto.h"
#include <common/dtor.h>
#include <limits.h>

result<void> callee(bool do_err) {
  if(do_err)
    return outcome::experimental::errc::argument_out_of_domain;
  return outcome::success();
}
