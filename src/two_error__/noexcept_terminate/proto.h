#pragma once

void caller() noexcept;
void callee() noexcept;
void caller2(int amount) noexcept;
void callee2(int amount) noexcept;
extern int global_int;
