#include "proto.h"

int main() {
  error_struct e;
  caller(e);
  if (e.error) {
    global_int = 0;
    e = error_struct{};
  }
  caller2(0, e);
  if (e.error) {
    global_int = 0;
    e = error_struct{};
  }
  return global_int;
}
