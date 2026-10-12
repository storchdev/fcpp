// std: c++17
// NRVO is optional: with two candidate locals a move is performed, and whether it is elided is up to the compiler.
#include <cstdio>

struct Tracked {
    int id;
    explicit Tracked(int i) : id(i) { std::printf("construct %d\n", id); }
    Tracked(Tracked&& o) noexcept : id(o.id) { std::printf("move %d\n", id); }
};

Tracked pick(bool first) {
    Tracked a(1), b(2);
    if (first) return a;
    return b;                                  // the compiler cannot construct both in the return slot
}

int main() {
    Tracked t = pick(true);
    std::printf("got %d\n", t.id);
}
