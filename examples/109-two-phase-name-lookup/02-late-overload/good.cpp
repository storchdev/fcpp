// std: c++17
#include <cstdio>

void f(double) { std::printf("f(double)\n"); }
void f(int) { std::printf("f(int)\n"); }           // declare every overload before the template that uses them

template <class T>
void call(T x) { f(x); }

int main() { call(1); }
