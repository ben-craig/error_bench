#include "proto.h"
#include <common/dtor.h>

void caller(error_struct &e) {
  Dtor d;
  callee(e);
}
