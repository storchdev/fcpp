// std: c++17
// sanitize: undefined
// Left-shifting a negative signed value is UB before C++20 (C++20 defines it as a modular shift).
#include <cstdio>

int scale(int x) { return x << 1; }            // UB in C++17 when x < 0

int main(int argc, char**) {
    int x = -argc;                             // -1
    std::printf("%d\n", scale(x));
}
