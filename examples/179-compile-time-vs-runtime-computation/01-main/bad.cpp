// std: c++20
// A constexpr function called with a non-constant argument, in a non-constant context, runs at run time.
#include <cstdio>
#include <type_traits>

constexpr int square(int x) { return std::is_constant_evaluated() ? -x * x : x * x; }   // the sign shows where it ran

int main(int argc, char**) {
    int n = argc + 4;                               // not a constant expression
    int a = square(n);                              // run time: -x*x branch is not taken
    int b = square(5);                              // initializer of a non-constexpr variable: the compiler may fold it, but it is not required to
    std::printf("square(n) = %d, square(5) = %d\n", a, b);
}
