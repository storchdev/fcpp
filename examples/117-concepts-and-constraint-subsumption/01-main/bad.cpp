// expect: compile-error
// std: c++20
// Subsumption compares atomic constraints by identity of the written expression, not by what it means.
#include <cstdio>
#include <type_traits>

template <class T> requires std::is_integral_v<T>
void f(T) { std::printf("integral\n"); }

template <class T> requires std::is_integral_v<T> && std::is_signed_v<T>
void f(T) { std::printf("signed integral\n"); }    // meant to be more specialised, but is_integral_v<T> here is a new atomic constraint

int main() { f(1); }                               // error: call of overloaded 'f(int)' is ambiguous
