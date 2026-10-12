// std: c++17
// also: good_b.cpp
#include <cstdio>

namespace { int scale() { return 2; } }            // internal linkage: each translation unit has its own
int a_value() { return scale() * 10; }
int b_value();

int main() { std::printf("a_value = %d, b_value = %d\n", a_value(), b_value()); }
