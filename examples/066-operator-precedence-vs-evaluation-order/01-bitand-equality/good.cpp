// std: c++17
#include <cstdio>

constexpr unsigned MASK = 0x4;

int main() {
    unsigned flags = 0x1;
    if ((flags & MASK) == 0)
        std::printf("bit 2 is clear\n");
    else
        std::printf("bit 2 is set\n");
}
