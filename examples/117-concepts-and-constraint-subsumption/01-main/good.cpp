// std: c++20
#include <concepts>
#include <cstdio>

template <class T> requires std::integral<T>
void f(T) { std::printf("integral\n"); }

template <class T> requires std::integral<T> && std::signed_integral<T>
void f(T) { std::printf("signed integral\n"); }    // both name the same concept std::integral, so it subsumes

int main() { f(1); }
