// std: c++17
// Compare sizes, not pointers: n <= end - buf never forms an out-of-range pointer.
#include <cstddef>
#include <cstdio>

bool fits(const char* buf, const char* end, std::size_t n) {
    return n <= static_cast<std::size_t>(end - buf);
}

int main() {
    char b[16];
    std::printf("fits(SIZE_MAX) = %d\n", fits(b, b + 16, static_cast<std::size_t>(-1)));
}
