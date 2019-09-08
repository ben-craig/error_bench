#include "proto.h"
#include "dtor__VALUE__.tmpl.h"
#include "common/nop.h"

result<void> caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  OUTCOME_TRYV(__NEXT_FUNC__(do_err));
  global_val = 0;
  return outcome::success();
}

result<void> param_caller__VALUE__(int *val, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  OUTCOME_TRYV(param___NEXT_FUNC__(val, do_err));
  *val = 0;
  return outcome::success();
}

result<int> ret_caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  OUTCOME_TRY(res, ret___NEXT_FUNC__(do_err));
  return res + 1;
}
