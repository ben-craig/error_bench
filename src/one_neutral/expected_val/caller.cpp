#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
tl::expected<void, int> caller() {
    Dtor d;
    tl::expected<void, int> e = callee();
    if(e)
        return e;
    ++global_int;
    return e;
}
