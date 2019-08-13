#include "proto.h"

void callee(bool do_err) {
  if(do_err)
    throw 1;
}
