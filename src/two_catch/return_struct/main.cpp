#include "proto.h"

int main()
{
    if(caller().error) {++global_int;}
    if(caller2(0).error) {++global_int;}
    return global_int;
}
