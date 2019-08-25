#include "proto.h"
#include "common/nop2.h"

int callee(bool do_err, int &) { 
  inline_nop_X X;
  if(do_err)
    return 1;
  return 0;
}
