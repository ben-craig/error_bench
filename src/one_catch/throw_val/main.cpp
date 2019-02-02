#include "proto.h"

int main() {
  try {
    caller();
  } catch (int) {
    ++global_int;
  }
  caller2(0);
  return global_int;
}
