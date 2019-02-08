#include "proto.h"

int main() {
  try {
    caller();
  } catch (int) {
    global_int = 0;
  }
  caller2(0);
  return global_int;
}
