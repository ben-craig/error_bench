#include "proto.h"
#include <exception>

int main() {
    try {caller();}
    catch(const std::exception &) {++global_int;}
    try {caller2(0);}
    catch(const std::exception &) {++global_int;}
    return global_int;
}
