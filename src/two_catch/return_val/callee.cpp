#include "proto.h"

int callee() {return 0;}
int callee2(int amount) {global_int+=amount; return 0;}
