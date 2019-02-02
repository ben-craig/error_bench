#include "proto.h"

int main()
{
    if(caller()) {++global_int;}
    if(caller2(0)) {++global_int;}
    return global_int;
}
