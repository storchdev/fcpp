// std: c++17
// sanitize: undefined
// Shifting by a count >= the width of the (promoted) left operand, or by a negative count, is UB.
#include <cstdio>

unsigned bit(int n) { return 1u << n; }        // UB when n >= 32 or n < 0

int main(int argc, char**) {
    int n = 31 + argc;                         // 32
    std::printf("%u\n", bit(n));
}
