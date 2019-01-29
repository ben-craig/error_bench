#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
error_struct caller() {
    Dtor d;
    error_struct e = callee();
    if(e.error)
        return e;
    ++global_int;
    return e;
}
