// std: c++17
// also: bad_lib.cpp
// expect: compile-error
// One translation unit is built with the old libstdc++ string ABI, the other with the new one: link error.
// ld: undefined reference to `greeting[abi:cxx11]()'
#include <cstdio>
#include <string>

std::string greeting();

int main() { std::printf("%s\n", greeting().c_str()); }
