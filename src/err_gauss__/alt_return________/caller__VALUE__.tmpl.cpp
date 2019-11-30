#include "proto.h"
#include "dtor__VALUE__.tmpl.h"
#include "common/nop.h"

//#define RETURN_ADDRESS_REF() \
//    (((void*volatile*)__builtin_frame_address(0))[7])

#define RETURN_ADDRESS_REF() *((void*volatile*)_AddressOfReturnAddress())

void caller__VALUE__(void *ret, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  __NEXT_FUNC__(&&retErr, do_err);
  if (__builtin_expect(hide_value(true), 1)) {
    global_val = 0;
    return;
  }
retErr:
  RETURN_ADDRESS_REF() = ret;
  return;
}

void param_caller__VALUE__(void *ret, int *val, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  param___NEXT_FUNC__(&&retErr, val, do_err);
  if (__builtin_expect(hide_value(true), 1)) {
    *val = 0;
    return;
  }
retErr:
  RETURN_ADDRESS_REF() = ret;
  return;
}

int ret_caller__VALUE__(void *ret, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  int retval = ret___NEXT_FUNC__(&&retErr, do_err) + 1;
  if (__builtin_expect(hide_value(true), 1)) {
    return retval;
  }
retErr:
  RETURN_ADDRESS_REF() = ret;
  return 0;
}

int ret_nd_caller__VALUE__(void *ret, bool do_err) {
  int retval = ret_nd___NEXT_FUNC__(&&retErr, do_err) + 1;
  if (__builtin_expect(hide_value(true), 1)) {
    return retval;
  }
retErr:
  RETURN_ADDRESS_REF() = ret;
  return 0;
}
