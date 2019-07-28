#include "proto.h"
#include <common/dtor.h>

thread_local int tls_error_val_var = 0;
void callee() {tls_error_val_var = 1;}
