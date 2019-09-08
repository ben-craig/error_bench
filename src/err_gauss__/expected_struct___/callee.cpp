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

tl::expected<void, error_struct> param_callee(int *val, bool do_err) {
  (void)val;
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

tl::expected<int, error_struct> ret_callee(bool do_err) {
  inline_nop_X X;
  if(do_err)
  {
    error_struct e;
    e.error = &error_info;
    e.domain = &error_domain;
    return tl::unexpected<error_struct>{e};
  }
  return 0;
}
