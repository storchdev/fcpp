// std: c++17
// `buf + n` with n beyond the array is already undefined, so the check cannot be relied on to reject n.
#include <cstddef>
#include <cstdio>

bool fits(const char* buf, const char* end, std::size_t n) {
    return buf + n <= end;          // UB when n > end - buf; with n == SIZE_MAX it also wraps
}

int main() {
    char b[16];
    std::printf("fits(SIZE_MAX) = %d\n", fits(b, b + 16, static_cast<std::size_t>(-1)));   // prints 1
}
