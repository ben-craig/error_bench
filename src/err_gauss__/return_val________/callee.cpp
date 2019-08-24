#include "proto.h"

int callee(bool do_err, int &) { 
  if(do_err)
    return 1;
  return 0;
}
