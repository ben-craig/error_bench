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

tl::expected<void, error_struct> param_caller__VALUE__(int *val, bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  tl::expected<void, error_struct> e = param___NEXT_FUNC__(val, do_err);
  if (!e)
    return e;
  *val = 0;
  return e;
}

tl::expected<int, error_struct> ret_caller__VALUE__(bool do_err) {
  NOP_SLED_HEAD___VALUE__;
  Dtor__VALUE__ d;
  tl::expected<int, error_struct> e = ret___NEXT_FUNC__(do_err);
  if (!e)
    return e;
  return *e+1;
}

tl::expected<int, error_struct> ret_nd_caller__VALUE__(bool do_err) {
  tl::expected<int, error_struct> e = ret_nd___NEXT_FUNC__(do_err);
  if (!e)
    return e;
  return *e+1;
}