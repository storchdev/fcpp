// std: c++17
#include <cstdio>

int scale(int x) { return x * 2; }             // same meaning, defined for negative x (overflow aside)

int main(int argc, char**) {
    int x = -argc;
    std::printf("%d\n", scale(x));
}
