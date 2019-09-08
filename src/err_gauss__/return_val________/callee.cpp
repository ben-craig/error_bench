#include "proto.h"
#include "common/nop2.h"

int callee(bool do_err) { 
  inline_nop_X X;
  if(do_err)
    return 1;
  return 0;
}

int param_callee(int *val, bool do_err) { 
  (void) val;
  inline_nop_X X;
  if(do_err)
    return 1;
  return 0;
}

int ret_callee(int *val, bool do_err) { 
  inline_nop_X X;
  if(do_err)
    return 1;
  *val = 0;
  return 0;
}
