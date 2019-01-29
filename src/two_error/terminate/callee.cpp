#include "proto.h"
#include <limits.h>
#include <stdlib.h>

void callee() {if(global_int == INT_MAX) abort();}
void callee2(int v) {if(global_int + v == INT_MAX) abort();}
