// std: c++17
// also: bad_b.cpp
// `derived` is initialized from `base`, which lives in another translation unit: their relative order is unspecified.
#include <cstdio>

extern int base;
int derived = base + 1;

int main() { std::printf("base = %d, derived = %d (expected 6)\n", base, derived); }
