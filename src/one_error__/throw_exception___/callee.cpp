#include "proto.h"
#include <exception>
#include <limits.h>

class err_exception : public std::exception {
public:
  int val;
  explicit err_exception(int e) : val(e) {}
  const char *what() const noexcept override { return ""; }
};

void callee() {
  if (global_int == INT_MAX)
    throw err_exception(1);
}
void callee2(int amount) { global_int += amount; }
