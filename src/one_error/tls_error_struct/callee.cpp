#include "proto.h"
#include <limits.h>

int error_info = 1;
int error_domain = 99;

void callee() {
  if (global_int == INT_MAX) {
    tls_error_struct_var.error = &error_info;
    tls_error_struct_var.domain = &error_domain;
    return;
  }
}
void callee2(int amount) { global_int += amount; }
thread_local error_struct tls_error_struct_var{};
