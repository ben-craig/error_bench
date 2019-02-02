#include "proto.h"
#include <common/dtor.h>

int caller() {
  Dtor d;
  return callee();
}
