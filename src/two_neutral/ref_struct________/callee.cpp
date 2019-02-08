#include "proto.h"

void callee(error_struct &) {}
void callee2(int amount, error_struct &) { global_int += amount; }
