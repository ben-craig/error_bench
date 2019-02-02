#include "proto.h"

int main() {
  try {
    caller();
  } catch (int) {
    ++global_int;
  }
  caller2(1);
  return global_int;
}
