#include "proto.h"
#include "dtor__VALUE__.tmpl.h"
#include "common/nop.h"

tl::expected<void, error_struct> caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  tl::expected<void, error_struct> e = __NEXT_FUNC__(do_err);
  if (!e)
    return e;
  global_val = 0;
  return e;
}
