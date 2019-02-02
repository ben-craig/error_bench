#include "proto.h"

int main() {
  try {
    caller();
  } catch (int) {
    global_int = 0;
  }
  try {
    caller2(0);
  } catch (int) {
    global_int = 0;
  }
  return global_int;
}
