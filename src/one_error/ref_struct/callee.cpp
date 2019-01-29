#include "proto.h"
#include <limits.h>

int error_info = 100;
int error_domain = 99;

void callee(error_struct &e) {
    if(global_int == INT_MAX)
    {
        e.error = &error_info;
        e.domain = &error_domain;
    }
}
void callee2(int amount, error_struct &) {}
