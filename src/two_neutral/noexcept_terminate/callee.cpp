#include "proto.h"

void callee() noexcept {}
void callee2(int amount) noexcept {global_int+=amount;}
