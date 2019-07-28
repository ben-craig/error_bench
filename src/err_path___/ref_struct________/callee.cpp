#include "proto.h"
#include <common/dtor.h>

void callee(error_struct &e) {
  e.error = &error_info;
  e.domain = &error_domain;
}
