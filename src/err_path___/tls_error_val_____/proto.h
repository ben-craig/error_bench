#pragma once

void caller(bool do_err, int depth);
void callee(bool do_err);
extern thread_local int tls_error_val_var;
extern int global_int;
