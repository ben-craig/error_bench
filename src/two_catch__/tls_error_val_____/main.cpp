#include "proto.h"

int main() {
  caller();
  if (tls_error_val_var) {
    tls_error_val_var = 0;
    global_int = 0;
  }
  caller2(0);
  if (tls_error_val_var) {
    tls_error_val_var = 0;
    global_int = 0;
  }
  return global_int;
}
