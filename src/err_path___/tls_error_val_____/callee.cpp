#include "proto.h"
#include <common/dtor.h>

thread_local int tls_error_val_var = 0;
void callee(bool do_err) {
  if(do_err)
    tls_error_val_var = 1;
}
