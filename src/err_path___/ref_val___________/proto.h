#pragma once

void caller(bool do_err, int depth, int &e);
void callee(bool do_err, int &e);
extern int global_int;
