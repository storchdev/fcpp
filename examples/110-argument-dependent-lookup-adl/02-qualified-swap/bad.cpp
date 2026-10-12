// std: c++17
// std::swap(a, b) is qualified, so a type's own swap in its namespace is never considered.
#include <cstdio>
#include <utility>

namespace lib {
struct Big { int x; };
inline int custom_calls = 0;
void swap(Big& a, Big& b) { ++custom_calls; std::swap(a.x, b.x); }
}

int main() {
    lib::Big a{1}, b{2};
    std::swap(a, b);                               // generic std::swap, not lib::swap
    std::printf("custom swap calls = %d\n", lib::custom_calls);
}
