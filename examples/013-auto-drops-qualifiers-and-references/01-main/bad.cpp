// std: c++17
// `auto` deduces a value type: the reference is dropped, so the loop mutates copies.
#include <cstdio>
#include <type_traits>
#include <vector>

struct Particle { double x; };

int main() {
    std::vector<Particle> ps{{1.0}, {2.0}};
    const Particle& ref = ps[0];

    auto copy = ref;  // Particle, not const Particle&: a copy, and a mutable one
    static_assert(std::is_same_v<decltype(copy), Particle>);
    copy.x = 99;      // compiles because top-level const was dropped; ps[0] is unaffected

    for (auto p : ps) // Particle by value: every element is copied
        p.x += 10;    // modifies the copy only

    std::printf("%g %g\n", ps[0].x, ps[1].x);  // prints "1 2", not "11 12"
}
