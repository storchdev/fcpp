// std: c++17
// uint8_t operands are promoted to int, so ~mask is a negative int, not an 8-bit value.
#include <cstdint>
#include <cstdio>

int main() {
    std::uint8_t mask = 0x0F;
    if (~mask == 0xF0)                                  // ~mask is int 0xFFFFFFF0, never equals 0xF0
        std::printf("~mask == 0xF0\n");
    else
        std::printf("~mask is %d, not 0xF0\n", ~mask);

    std::uint8_t a = 200, b = 100;
    auto sum = a + b;                                   // int 300, not a wrapped uint8_t
    std::printf("a + b = %d, sizeof(a + b) = %zu\n", sum, sizeof(a + b));
}
