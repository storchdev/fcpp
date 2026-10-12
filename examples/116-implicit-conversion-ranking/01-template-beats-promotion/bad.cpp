// std: c++17
// A template that matches exactly beats a non-template that needs an integral promotion.
#include <cstdio>

void g(int) { std::printf("g(int)\n"); }
template <class T> void g(T) { std::printf("g(T)\n"); }

int main() {
    g('a');                                        // char -> int is a promotion; T = char is exact
}
