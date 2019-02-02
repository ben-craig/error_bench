#include "proto.h"
#include <limits.h>

int error_info = 1;
int error_domain = 99;

void callee() {
  if (global_int == INT_MAX) {
    error_struct e;
    e.error = &error_info;
    e.domain = &error_domain;
    throw e;
  }
}
void callee2(int amount) { global_int += amount; }
