#include "proto.h"
#include "common/nop2.h"

result<void> callee(bool do_err) { 
  inline_nop_X X;
  if(do_err)
    return outcome::experimental::errc::argument_out_of_domain;
  return outcome::success();
}

result<void> param_callee(int *val, bool do_err) { 
  (void)val;
  inline_nop_X X;
  if(do_err)
    return outcome::experimental::errc::argument_out_of_domain;
  return outcome::success();
}

result<int> ret_callee(bool do_err) { 
  inline_nop_X X;
  if(do_err)
    return outcome::experimental::errc::argument_out_of_domain;
  return outcome::success(0);
}

result<int> ret_nd_callee(bool do_err) { 
  inline_nop_X X;
  if(do_err)
    return outcome::experimental::errc::argument_out_of_domain;
  return outcome::success(0);
}
