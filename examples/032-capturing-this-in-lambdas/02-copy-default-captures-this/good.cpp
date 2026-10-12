// std: c++17
// Copy the member explicitly with an init-capture (or capture [*this]).
#include <cstdio>

struct Counter {
    int n = 1;
    auto snapshot() { return [n = n] { return n; }; }
};

int main() {
    Counter c;
    auto snap = c.snapshot();
    c.n = 99;
    std::printf("snapshot sees %d\n", snap());       // 1
}
