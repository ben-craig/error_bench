#pragma once

void caller();
void callee();
void caller2(int amount);
void callee2(int amount);
extern thread_local int tls_error_val_var;
extern int global_int;
