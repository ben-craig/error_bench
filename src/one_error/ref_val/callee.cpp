#include "proto.h"
#include <limits.h>

void callee(int &e) {
    if(global_int == INT_MAX)
    {
        e = 1;
        return;
    }
}
void callee2(int amount, int &) {global_int+=amount;}
