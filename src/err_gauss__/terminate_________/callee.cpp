#include "proto.h"
#include <stdlib.h>

void callee(bool do_err, int &) {
  if(do_err)
    abort();
}
