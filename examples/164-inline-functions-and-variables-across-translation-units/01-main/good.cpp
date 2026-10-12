// std: c++17
// also: good_b.cpp
#include "good_shared.h"
#include <cstdio>

int b_value();

int main() { std::printf("%d %d\n", twice(2), b_value()); }
