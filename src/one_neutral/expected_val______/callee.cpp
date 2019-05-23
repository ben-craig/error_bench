#include "proto.h"
#include <common/dtor.h>

tl::expected<void, int> callee() { NOP_SLED_TAIL_2; return {}; }
