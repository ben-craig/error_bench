#include "proto.h"

int error_info = 1;
int error_domain = 99;

void callee(bool do_err) {
  if(do_err)
  {
    error_struct e;
    e.error = &error_info;
    e.domain = &error_domain;
    throw e;
  }
}
