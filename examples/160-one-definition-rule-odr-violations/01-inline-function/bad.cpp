// std: c++17
// also: bad_b.cpp
// Two translation units define inline `scale()` differently: ill-formed, no diagnostic required.
#include <cstdio>

inline int scale() { return 2; }
int a_value() { return scale() * 10; }
int b_value();

int main() { std::printf("a_value = %d, b_value = %d\n", a_value(), b_value()); }
