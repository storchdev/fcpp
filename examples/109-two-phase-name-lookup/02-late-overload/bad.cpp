// std: c++17
// For a dependent call, ordinary unqualified lookup only sees declarations visible at the template definition.
#include <cstdio>

void f(double) { std::printf("f(double)\n"); }

template <class T>
void call(T x) { f(x); }                           // dependent call

void f(int) { std::printf("f(int)\n"); }           // declared after the template: not found for int (no ADL for int)

int main() { call(1); }
