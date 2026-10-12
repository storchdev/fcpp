// std: c++17
// The offset of a virtual base inside a class depends on the most-derived type, so it cannot be computed once.
#include <cstddef>
#include <cstdio>

struct V { int v = 7; };
struct L : virtual V { int l = 1; };
struct R : virtual V { int r = 2; };
struct D : L, R { int d = 3; };

int main() {
    L alone;
    std::ptrdiff_t off = reinterpret_cast<char*>(static_cast<V*>(&alone)) - reinterpret_cast<char*>(&alone);

    D d;
    L* lp = &d;
    V* real = static_cast<V*>(lp);             // found through the vtable at run time
    V* guess = reinterpret_cast<V*>(reinterpret_cast<char*>(lp) + off);   // offset taken from a standalone L
    std::printf("sizeof(L)=%zu sizeof(D)=%zu\n", sizeof(L), sizeof(D));
    std::printf("offset of V in standalone L = %td, in L-inside-D = %td\n", off,
                reinterpret_cast<char*>(real) - reinterpret_cast<char*>(lp));
    std::printf("guess == real: %d, real->v = %d\n", guess == real, real->v);
}
