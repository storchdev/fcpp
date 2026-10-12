// std: c++17
// Writing one union member and reading another is undefined in C++ (it is allowed in C).
#include <cstdint>
#include <cstdio>

union Bits {
    float f;
    std::uint32_t u;
};

int main() {
    Bits b;
    b.f = 1.0f;
    std::printf("%08x\n", b.u);     // reads the inactive member
}
