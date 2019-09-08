#include "common/nop2.h"
#include "proto.h"
#include <stdlib.h>

void callee(bool do_err) {
  inline_nop_X X;
  if(do_err)
    abort();
}

void param_callee(int *val, bool do_err) {
  (void) val;
  inline_nop_X X;
  if(do_err)
    abort();
}

int ret_callee(bool do_err) {
  inline_nop_X X;
  if(do_err)
    abort();
  return 0;
}

