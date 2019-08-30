#include "proto.h"
#include "common/nop2.h"

int error_info = 1;
int error_domain = 99;

error_struct callee(bool do_err) {
  inline_nop_X X;
  error_struct e;
  if(do_err)
  {
    e.error = &error_info;
    e.domain = &error_domain;
  }
  return e;
}
