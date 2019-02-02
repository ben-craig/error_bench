#include "proto.h"

int main() {
  try {
    caller();
  } catch (const error_struct &) {
    global_int = 0;
  }
  caller2(0);
  return global_int;
}
