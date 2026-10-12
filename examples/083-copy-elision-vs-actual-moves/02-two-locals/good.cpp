// std: c++17
#include <cstdio>

struct Tracked {
    int id;
    explicit Tracked(int i) : id(i) { std::printf("construct %d\n", id); }
    Tracked(Tracked&& o) noexcept : id(o.id) { std::printf("move %d\n", id); }
};

Tracked pick(bool first) {
    return first ? Tracked(1) : Tracked(2);    // prvalue operands: guaranteed elision, only one object is built
}

int main() {
    Tracked t = pick(true);
    std::printf("got %d\n", t.id);
}
