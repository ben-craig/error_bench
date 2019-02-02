#include "proto.h"
#include <common/dtor.h>

void caller(int &e) {
  Dtor d;
  callee(e);
}
