// std: c++17
// also: good_b.cpp
#include <cstdio>

int& base();                                       // construct on first use
int derived = base() + 1;

int main() { std::printf("base = %d, derived = %d (expected 6)\n", base(), derived); }
