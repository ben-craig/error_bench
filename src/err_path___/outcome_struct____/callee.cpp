#include "proto.h"
#include <common/dtor.h>
#include <limits.h>

int error_info = 1;
int error_domain = 99;

result<void, error_struct> callee(bool do_err) {
  if(do_err)
  {
    error_struct e;
    e.error = &error_info;
    e.domain = &error_domain;
    return outcome::failure(e);
  }
  return outcome::success();
}
