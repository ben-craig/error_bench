#include "proto.h"
#include <common/dtor.h>

void callee() {NOP_SLED_TAIL_2;}
thread_local error_struct tls_error_struct_var{};
