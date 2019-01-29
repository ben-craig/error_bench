#include "proto.h"
#include <limits.h>

int error_info = 1;
int error_domain = 99;

error_struct callee() {
    if(global_int == INT_MAX)
    {
        error_struct e;
        e.error = &error_info;
        e.domain = &error_domain;
        return e;
    }
    return error_struct{};
}
error_struct callee2(int) {return error_struct{};}
