// std: c++17
#include <cstdio>
#include <utility>

namespace lib {
struct Big { int x; };
inline int custom_calls = 0;
void swap(Big& a, Big& b) { ++custom_calls; std::swap(a.x, b.x); }
}

int main() {
    lib::Big a{1}, b{2};
    using std::swap;                               // fallback for types without their own swap
    swap(a, b);                                    // unqualified: ADL finds lib::swap
    std::printf("custom swap calls = %d\n", lib::custom_calls);
}
