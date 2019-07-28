#pragma once

void caller(int depth);
void callee();
extern thread_local int tls_error_val_var;
extern int global_int;
