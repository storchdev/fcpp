// std: c++17
#include <cstdio>

struct V { int v = 7; };
struct L : virtual V { int l = 1; };
struct R : virtual V { int r = 2; };
struct D : L, R { int d = 3; };

int main() {
    D d;
    L* lp = &d;
    R* rp = &d;
    V* via_l = lp;                             // let the compiler find the virtual base each time
    V* via_r = rp;
    std::printf("via L == via R: %d, v = %d\n", via_l == via_r, via_l->v);
}
