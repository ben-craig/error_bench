#include "common/nop2.h"
#include "proto.h"
#include <stdlib.h>

#define RETURN_ADDRESS_REF *((void*volatile*)_AddressOfReturnAddress())
//#define RETURN_ADDRESS_REF (((void*volatile*)__builtin_frame_address(0))[1])

void callee(void *ret, bool do_err) {
  inline_nop_X X;
  if(do_err)
    RETURN_ADDRESS_REF = ret;
}

void param_callee(void *ret, int *val, bool do_err) {
  (void) val;
  inline_nop_X X;
  if(do_err)
    RETURN_ADDRESS_REF = ret;
}

int ret_callee(void *ret, bool do_err) {
  inline_nop_X X;
  if(do_err)
    RETURN_ADDRESS_REF = ret;
  return 0;
}

int ret_nd_callee(void *ret, bool do_err) {
  inline_nop_X X;
  if(do_err)
    RETURN_ADDRESS_REF = ret;
  return 0;
}
