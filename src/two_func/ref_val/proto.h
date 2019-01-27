#pragma once

void caller(int &e);
void callee(int &e);
void caller2(int amount, int &e);
void callee2(int amount, int &e);
extern int global_int;
