#include "proto.h"
#include "dtor__VALUE__.tmpl.h"
#include "common/nop.h"

int global_int = 0;
void caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  __NEXT_FUNC__(do_err);
  global_int = 0;
}
