#include "proto.h"

int main() {
  caller();
  if (tls_error_struct_var.error) {
    tls_error_struct_var = error_struct{};
    ++global_int;
  }
  caller2(0);
  return global_int;
}
