#include "proto.h"

int main() {
    try { caller(); }
    catch(int) {++global_int;}
    try {caller2(0); }
    catch(int) {++global_int;}
    return global_int;
}
