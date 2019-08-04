#include "proto.h"
#include <common/dtor.h>
#include <exception>

class err_exception : public std::exception {
public:
  int val;
  explicit err_exception(int e) : val(e) {}
  const char *what() const noexcept override { return ""; }
};

void callee(bool do_err) {
  if(do_err)
    throw err_exception(1);
}
