#include "proto.h"
#include <common/dtor.h>

thread_local error_struct tls_error_struct_var{};
int error_info = 1;
int error_domain = 99;
void callee(bool do_err) {
  if(do_err)
  {
    tls_error_struct_var.error = &error_info;
    tls_error_struct_var.domain = &error_domain;
  }
}
