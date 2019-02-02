#include "proto.h"
#include <common/dtor.h>

error_struct caller() {
  Dtor d;
  return callee();
}
