// std: c++17
#include <climits>
#include <cstdio>
#include <optional>

// Test BEFORE the operation, using only values that cannot overflow.
bool will_overflow(int x) { return x == INT_MAX; }

// Or use the compiler's checked arithmetic (GCC/Clang) and get a result + flag.
std::optional<int> checked_add(int a, int b) {
    int out;
    if (__builtin_add_overflow(a, b, &out)) return std::nullopt;
    return out;
}

// Or do the arithmetic in unsigned, where wraparound is defined, if wrap is what you want.
int wrapping_add(int a, int b) {
    return static_cast<int>(static_cast<unsigned>(a) + static_cast<unsigned>(b));  // implementation-defined pre-C++20, two's complement since C++20
}

int main() {
    std::printf("will_overflow(INT_MAX) = %d\n", will_overflow(INT_MAX));
    auto r = checked_add(INT_MAX, 1);
    std::printf("checked_add(INT_MAX,1) has_value=%d\n", r.has_value());
    std::printf("wrapping_add(INT_MAX,1) = %d\n", wrapping_add(INT_MAX, 1));
}
