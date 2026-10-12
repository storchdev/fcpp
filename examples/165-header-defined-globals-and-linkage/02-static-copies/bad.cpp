// std: c++17
// also: bad_b.cpp
// `static` (or `const`) at namespace scope gives internal linkage: every translation unit gets its own, independent variable.
#include "bad_shared.h"
#include <cstdio>

void bump();

int main() { bump(); std::printf("counter = %d (expected 1)\n", counter); }
