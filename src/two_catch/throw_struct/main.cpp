#include "proto.h"

int main() {
  try {
    caller();
  } catch (const error_struct &) {
    ++global_int;
  }
  try {
    caller2(0);
  } catch (const error_struct &) {
    ++global_int;
  }
  return global_int;
}
