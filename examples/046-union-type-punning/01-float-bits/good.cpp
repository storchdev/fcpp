// std: c++20
// std::bit_cast copies the object representation into a new object of the other type.
#include <bit>
#include <cstdint>
#include <cstdio>

int main() {
    const auto u = std::bit_cast<std::uint32_t>(1.0f);
    std::printf("%08x\n", u);
}
