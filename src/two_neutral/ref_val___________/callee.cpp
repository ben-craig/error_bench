#include "proto.h"

void callee(int &) {}
void callee2(int amount, int &) { global_int += amount; }
