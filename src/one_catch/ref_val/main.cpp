#include "proto.h"

int main() {
  int e = 0;
  caller(e);
  if (e) {
    ++global_int;
    e = 0;
  }
  caller2(0, e);
  return global_int;
}
