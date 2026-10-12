// std: c++17
// sanitize: undefined
// INT_MIN / -1 is not representable in int, so it is UB (and traps on x86).
#include <climits>
#include <cstdio>

int divide(int a, int b) { return a / b; }     // UB if a == INT_MIN && b == -1

int main(int argc, char**) {
    int minus_one = -argc;                     // -1, but not a compile-time constant
    std::printf("%d\n", divide(INT_MIN, minus_one));
}
