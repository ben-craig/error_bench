#include "proto.h"
#include <common/dtor.h>

void callee(bool do_err, int &e) { 
  if(do_err)
    e = 1;
}
