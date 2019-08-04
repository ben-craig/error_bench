#include "proto.h"
#include <common/dtor.h>
#include <stdlib.h>

void callee(bool do_err) {
  if(do_err)
    abort();
}
