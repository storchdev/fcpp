// std: c++17
#include <cstdio>

void g(int) { std::printf("g(int)\n"); }
template <class T> void g(T) { std::printf("g(T)\n"); }

int main() {
    g(static_cast<int>('a'));                      // exact match for the non-template
    g<>(1);                                        // or explicitly ask for the template
}
