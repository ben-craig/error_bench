#include "proto.h"
#include <common/dtor.h>

int callee(bool do_err) { 
  if(do_err)
    return 1;
  return 0;
}
