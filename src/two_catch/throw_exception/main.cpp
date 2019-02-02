#include "proto.h"
#include <exception>

int main() {
  try {
    caller();
  } catch (const std::exception &) {
    global_int = 0;
  }
  try {
    caller2(0);
  } catch (const std::exception &) {
    global_int = 0;
  }
  return global_int;
}
