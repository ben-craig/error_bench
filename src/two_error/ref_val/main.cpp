#include "proto.h"

int main() {
  int e = 0;
  caller(e);
  caller2(0, e);
  return global_int;
}
