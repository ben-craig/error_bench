#include "proto.h"

void callee() {}
void callee2(int amount) { global_int += amount; }
thread_local int tls_error_val_var = 0;
