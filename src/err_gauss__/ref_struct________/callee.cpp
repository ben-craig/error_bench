#include "proto.h"
#include "common/nop2.h"

int error_info = 1;
int error_domain = 99;

void callee(bool do_err, error_struct &e) {
  inline_nop_X X;
  if(do_err)
  {
    e.error = &error_info;
    e.domain = &error_domain;
  }
}
