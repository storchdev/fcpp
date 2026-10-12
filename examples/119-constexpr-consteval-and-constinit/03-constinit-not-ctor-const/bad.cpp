// expect: compile-error
// std: c++20
// constinit requires constant initialization, but the variable stays mutable (it is not const).
#include <cstdio>

int runtime_value() { return 42; }

constinit int g = runtime_value();                 // error: initializer is not a constant expression

int main() { std::printf("%d\n", g); }
