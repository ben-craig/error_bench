#include "proto.h"
#include <limits.h>

void callee() {
  if (global_int == INT_MAX) {
    tls_error_val_var = 1;
    return;
  }
}
void callee2(int amount) { global_int += amount; }
thread_local int tls_error_val_var = 0;
