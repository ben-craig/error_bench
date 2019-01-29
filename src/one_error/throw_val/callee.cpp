#include "proto.h"
#include <limits.h>

void callee() {if(global_int == INT_MAX) throw 1;}
void callee2(int amount) {global_int+=amount;}
