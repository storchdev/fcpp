// expect: compile-error
// std: c++20
// A consteval function must be called in a constant expression every time; a runtime argument is an error.
#include <cstdio>

consteval int square(int n) { return n * n; }

int main() {
    int n = 5;
    std::printf("%d\n", square(n));                // error: 'n' is not a constant expression
}
