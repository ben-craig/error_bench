#include "proto.h"
#include <common/dtor.h>

thread_local error_struct tls_error_struct_var{};
void callee() {
  tls_error_struct_var.error = &error_info;
  tls_error_struct_var.domain = &error_domain;
}
