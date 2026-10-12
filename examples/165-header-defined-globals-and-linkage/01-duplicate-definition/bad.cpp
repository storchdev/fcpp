// std: c++17
// also: bad_b.cpp
// expect: compile-error
// A global variable defined in a header is defined in every translation unit that includes it: link error.
// ld: multiple definition of `counter'
#include "bad_shared.h"
#include <cstdio>

void bump();

int main() { bump(); std::printf("counter = %d\n", counter); }
