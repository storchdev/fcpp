// std: c++17
// also: bad_b.cpp
// expect: compile-error
// A non-inline function defined in a header is defined once per including translation unit: link error (multiple definition).
// ld: multiple definition of `twice(int)'
#include "bad_shared.h"
#include <cstdio>

int b_value();

int main() { std::printf("%d %d\n", twice(2), b_value()); }
