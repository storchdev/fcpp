// std: c++17
// Floating-point addition is not associative: the grouping changes the rounded result.
#include <cstdio>

int main(int argc, char**) {
    double big = 1e16 * argc;                  // 1e16, but not a compile-time constant
    double a = big, b = -big, c = 1.0;
    std::printf("(a + b) + c = %g\n", (a + b) + c);   // 1
    std::printf("a + (b + c) = %g\n", a + (b + c));   // 0: b + c rounds back to -1e16
}
