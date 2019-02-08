#include "proto.h"

int main() {
  if (caller().error) {
    global_int = 0;
  }
  caller2(0);
  return global_int;
}
