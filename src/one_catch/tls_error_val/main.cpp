#include "proto.h"

int main() {
  caller();
  if (tls_error_val_var) {
    tls_error_val_var = 0;
    ++global_int;
  }
  caller2(0);
  return global_int;
}