// std: c++17
#include <cstdint>
#include <cstdio>

int main() {
    std::uint8_t mask = 0x0F;
    std::uint8_t inv = static_cast<std::uint8_t>(~mask);   // narrow back explicitly
    if (inv == 0xF0)
        std::printf("~mask == 0xF0\n");

    std::uint8_t a = 200, b = 100;
    std::uint8_t wrapped = static_cast<std::uint8_t>(a + b);   // if 8-bit wrap is what you want, say so
    std::printf("a + b as uint8_t = %d\n", wrapped);
}
