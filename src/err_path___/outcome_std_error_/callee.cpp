#include "proto.h"
#include <common/dtor.h>
#include <limits.h>

result<void> callee() {
  return outcome::experimental::errc::argument_out_of_domain;
}
