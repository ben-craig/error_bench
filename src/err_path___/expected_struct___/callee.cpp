#include "proto.h"
#include <common/dtor.h>

tl::expected<void, error_struct> callee() {
  error_struct e;
  e.error = &error_info;
  e.domain = &error_domain;
  return tl::unexpected<error_struct>{e};
}
