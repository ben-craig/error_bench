#include "proto.h"
#include <common/dtor.h>

tl::expected<void, int> callee(bool do_err) {
  if(do_err)
    return tl::unexpected<int>{1};
  return {};
}
