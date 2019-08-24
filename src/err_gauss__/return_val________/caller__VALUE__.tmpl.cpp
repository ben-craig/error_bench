#include "proto.h"
#include "dtor__VALUE__.tmpl.h"
#include "common/nop.h"

int caller__VALUE__(bool do_err, int &param) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  int e = __NEXT_FUNC__(do_err, param);
  if (e)
    return e;
  param = 0;
  return 0;
}
