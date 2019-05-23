#include "proto.h"
#include <common/dtor.h>

tl::expected<void, error_struct> callee() { NOP_SLED_TAIL_2; return {}; }
