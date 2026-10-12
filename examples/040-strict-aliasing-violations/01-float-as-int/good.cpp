// std: c++20
// Copy the bytes with std::bit_cast (or memcpy) instead of accessing one object through two types.
#include <bit>
#include <cstdint>
#include <cstdio>

std::uint32_t float_bits(float f) { return std::bit_cast<std::uint32_t>(f); }

int main() {
    std::printf("%08x\n", float_bits(2.0f));
}
