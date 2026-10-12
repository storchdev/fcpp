// std: c++17
// Spell the reference: `auto&` keeps the object (and its constness), `const auto&` reads without copying.
#include <cstdio>
#include <type_traits>
#include <vector>

struct Particle { double x; };

int main() {
    std::vector<Particle> ps{{1.0}, {2.0}};
    const Particle& ref = ps[0];

    const auto& view = ref;  // const Particle&: no copy, no mutation
    static_assert(std::is_same_v<decltype(view), const Particle&>);
    // view.x = 99;          // error: assignment of member in read-only object

    for (auto& p : ps)       // Particle&: mutates the elements
        p.x += 10;

    std::printf("%g %g\n", ps[0].x, ps[1].x);  // 11 12
}
