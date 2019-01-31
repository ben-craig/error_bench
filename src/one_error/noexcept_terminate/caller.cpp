#include "proto.h"
#include <common/dtor.h>

int global_int = 0;
void caller() noexcept {
    Dtor d;
    callee();
    ++global_int;
}

void caller2(int amount) noexcept {
    Dtor d;
    callee2(amount);
    global_int+=amount;
}
