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
