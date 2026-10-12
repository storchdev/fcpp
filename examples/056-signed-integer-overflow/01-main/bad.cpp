// std: c++17
// sanitize: undefined
// Signed overflow is UB, so the compiler may assume it never happens.
#include <climits>
#include <cstdio>

bool will_overflow(int x) {
    return x + 1 < x;     // "obviously" true for INT_MAX... but the compiler folds it to false
}

int count_up(int start) {
    int n = 0;
    for (int i = start; i >= start; ++i) {   // intended to stop at wraparound; UB instead
        if (++n > 10) break;
    }
    return n;
}

int main() {
    std::printf("will_overflow(INT_MAX) = %d\n", will_overflow(INT_MAX));  // 0 with GCC (any -O) and clang -O2; 1 with clang -O0 or -fwrapv
    std::printf("count_up(INT_MAX-3) = %d\n", count_up(INT_MAX - 3));
}
