#include "common/nop2.h"
#include "proto.h"
#include <stdlib.h>

void callee(bool do_err) {
  inline_nop_X X;
  if(do_err)
    abort();
}