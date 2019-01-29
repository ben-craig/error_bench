#include "proto.h"

tl::expected<void, int> callee() {return {};}
tl::expected<void, int> callee2(int) {return {};}
