#include "proto.h"
#include <common/dtor.h>

void callee(bool do_err) {
  if(do_err)
    throw 1;
}
