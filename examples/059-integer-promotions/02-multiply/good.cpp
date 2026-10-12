// std: c++17
#include <cstdint>
#include <cstdio>

int main() {
    std::uint16_t a = 65535, b = 65535;
    std::uint32_t product = std::uint32_t{a} * b;   // promote to unsigned first: wraps (defined) instead of overflowing int
    std::printf("%u\n", product);
}
