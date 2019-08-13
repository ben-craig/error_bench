#include "proto.h"
#include <stdlib.h>

void callee(bool do_err) {
  if(do_err)
    abort();
}
