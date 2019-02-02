#include "proto.h"

int main() {
  if (caller()) {
    global_int = 0;
  }
  if (caller2(0)) {
    global_int = 0;
  }
  return global_int;
}
