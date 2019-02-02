#include "proto.h"

int main() {
    error_struct e;
    caller(e);
    if(e.error) {
        ++global_int;
        e = error_struct{};
    }
    caller2(0, e);
    return global_int;
}
