#include "proto.h"
#include "common/nop2.h"

int error_info = 1;
int error_domain = 99;

tl::expected<void, error_struct> callee(bool do_err) {
  inline_nop_X X;
  if(do_err)
  {
    error_struct e;
    e.error = &error_info;
    e.domain = &error_domain;
    return tl::unexpected<error_struct>{e};
  }
  return {};
}
