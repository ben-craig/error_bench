#include "proto.h"
#include "dtor__VALUE__.tmpl.h"
#include "common/nop.h"

int caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  int e = __NEXT_FUNC__(do_err);
  if (e)
    return e;
  global_val = 0;
  return 0;
}

int param_caller__VALUE__(int *val, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  int e = param___NEXT_FUNC__(val, do_err);
  if (e)
    return e;
  *val = 0;
  return 0;
}

int ret_caller__VALUE__(int *val, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  int out_val = 0;
  int e = ret___NEXT_FUNC__(&out_val, do_err);
  if (e)
    return e;
  *val = out_val + 1;
  return 0;
}
