// std: c++17
// also: good_b.cpp
#include "good_shared.h"
#include <cstdio>

void bump();

int main() { bump(); std::printf("counter = %d\n", counter); }
