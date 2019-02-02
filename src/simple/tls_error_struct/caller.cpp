#include "proto.h"
#include <common/dtor.h>

void caller() {
  Dtor d;
  callee();
}
