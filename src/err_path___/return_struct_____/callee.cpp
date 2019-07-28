#include "proto.h"
#include <common/dtor.h>


error_struct callee() {
  error_struct e;
  e.error = &error_info;
  e.domain = &error_domain;
  return e;
}
