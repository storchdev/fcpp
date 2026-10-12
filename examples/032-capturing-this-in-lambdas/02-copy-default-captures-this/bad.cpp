// std: c++17
// `[=]` looks like "copy everything", but members are accessed through the captured `this` pointer.
#include <cstdio>

struct Counter {
    int n = 1;
    auto snapshot() { return [=] { return n; }; }   // captures `this`, not a copy of n
};

int main() {
    Counter c;
    auto snap = c.snapshot();
    c.n = 99;
    std::printf("snapshot sees %d\n", snap());       // 99, not 1
}
