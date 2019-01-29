#include "proto.h"
#include <limits.h>
#include <exception>

class err_exception : public std::exception
{
public:
    int val;
    explicit err_exception(int e) : val(e) {}
    const char *what() const override {return "";}
};

void callee() {if(global_int == INT_MAX) throw err_exception(1);}
void callee2(int amount) {
    if(global_int + amount == INT_MAX)
        throw err_exception(1);
    global_int+=amount;
}
