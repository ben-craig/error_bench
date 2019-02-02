#include "proto.h"

error_struct callee() { return error_struct{}; }
error_struct callee2(int amount) {
  global_int += amount;
  return error_struct{};
}
