// expect: compile-error
// std: c++17
// After a dependent object expression, a member template name needs the `template` keyword before `<`.
#include <cstdio>

struct Maker {
    template <class U> U make() const { return U(); }
};

template <class M>
void g(const M& m) {
    int x = m.make<int>();                         // parsed as (m.make < int) > ()
    std::printf("%d\n", x);
}

int main() { g(Maker{}); }
