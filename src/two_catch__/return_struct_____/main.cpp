#include "proto.h"

int main() {
  if (caller().error) {
    global_int = 0;
  }
  if (caller2(0).error) {
    global_int = 0;
  }
  return global_int;
}
