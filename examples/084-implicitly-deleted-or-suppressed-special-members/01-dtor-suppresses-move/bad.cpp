// std: c++17
// A user-declared destructor suppresses the implicit move constructor, so "moves" silently become copies.
#include <cstdio>
#include <utility>

struct Tracker {
    Tracker() = default;
    Tracker(const Tracker&) { std::puts("copy"); }
    Tracker(Tracker&&) noexcept { std::puts("move"); }
};

struct Plain { Tracker t; };
struct WithDtor {
    Tracker t;
    ~WithDtor() { std::puts("cleanup"); }      // user-declared: no implicit move constructor
};

int main() {
    Plain p;
    Plain p2 = std::move(p);                   // "move"
    WithDtor w;
    WithDtor w2 = std::move(w);                // "copy"
    (void)p2;
}
