// std: c++17
// `==` binds tighter than `&`, so `flags & MASK == 0` is `flags & (MASK == 0)`.
#include <cstdio>

constexpr unsigned MASK = 0x4;

int main() {
    unsigned flags = 0x1;                      // bit 2 is clear
    if (flags & MASK == 0)                     // parsed as flags & (MASK == 0), i.e. flags & 0
        std::printf("bit 2 is clear\n");
    else
        std::printf("bit 2 is set (wrong)\n");
}
