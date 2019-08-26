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
