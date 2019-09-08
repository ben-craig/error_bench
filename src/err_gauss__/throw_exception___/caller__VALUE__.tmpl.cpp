#include "proto.h"
#include "dtor__VALUE__.tmpl.h"
#include "common/nop.h"

void caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  __NEXT_FUNC__(do_err);
  global_val = 0;
}

void param_caller__VALUE__(int *val, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  param___NEXT_FUNC__(val, do_err);
  *val = 0;
}

int ret_caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  return ret___NEXT_FUNC__(do_err) + 1;
}

