#include "proto.h"

void callee() {}
void callee2(int amount) { global_int += amount; }
thread_local error_struct tls_error_struct_var{};
