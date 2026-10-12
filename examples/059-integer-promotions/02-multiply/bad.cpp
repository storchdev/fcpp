// std: c++17
// sanitize: undefined
// uint16_t * uint16_t is done in (signed) int, so 65535 * 65535 overflows int: UB despite "unsigned" types.
#include <cstdint>
#include <cstdio>

int main() {
    std::uint16_t a = 65535, b = 65535;
    std::uint32_t product = a * b;          // promoted to int: 4294836225 does not fit in a 32-bit int
    std::printf("%u\n", product);
}
