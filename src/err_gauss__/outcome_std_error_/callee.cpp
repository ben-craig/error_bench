#include "proto.h"
#include "common/nop2.h"

result<void> callee(bool do_err) { 
  inline_nop_X X;
  if(do_err)
    return outcome::experimental::errc::argument_out_of_domain;
  return outcome::success();
}

