#include "proto.h"
#include <common/dtor.h>

int error_info = 1;
int error_domain = 99;

void callee() {
  error_struct e;
  e.error = &error_info;
  e.domain = &error_domain;
  throw e;
}
