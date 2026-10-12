// std: c++20
#include <cstdio>
#include <type_traits>

constexpr int square(int x) { return std::is_constant_evaluated() ? -x * x : x * x; }   // the sign shows where it ran

int main() {
    constexpr int b = square(5);                    // required constant expression: evaluated at compile time
    std::printf("square(5) = %d (negative means compile time)\n", b);
}
