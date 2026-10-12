// std: c++17
#include <cstdio>

struct Meter {
    Meter(int v = 0) : value(v) {}
    int value;
    friend void inspect(const Meter& m) { std::printf("%d m\n", m.value); }
};

int main() {
    inspect(Meter{3});
    inspect(Meter(3));                             // convert explicitly so ADL has a Meter to look at
}
