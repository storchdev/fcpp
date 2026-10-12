// std: c++17
#include <cstdio>

template <class T> void f(T) { std::printf("f(T)\n"); }
template <class T> void f(T*) { std::printf("f(T*)\n"); }
template <> void f<int>(int*) { std::printf("f<int>(int*): specialization of #2\n"); }   // specializes the overload that is chosen

int main() {
    int x = 0;
    f(&x);
}
