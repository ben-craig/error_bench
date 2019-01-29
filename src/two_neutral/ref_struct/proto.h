#pragma once

struct error_struct
{
    void *error = nullptr;
    void *domain = nullptr;
};
void caller(error_struct &e);
void callee(error_struct &e);
void caller2(int amount, error_struct &e);
void callee2(int amount, error_struct &e);
extern int global_int;
