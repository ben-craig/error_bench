#include "proto.h"
#include <common/dtor.h>

void callee() {NOP_SLED_TAIL_2;}
thread_local int tls_error_val_var = 0;
