#include "proto.h"
#include <common/dtor.h>

int error_info = 1;
int error_domain = 99;

error_struct callee(bool do_err) {
  error_struct e;
  if(do_err)
  {
    e.error = &error_info;
    e.domain = &error_domain;
  }
  return e;
}
