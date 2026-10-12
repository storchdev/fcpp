// std: c++17
// sanitize: address
// A raw owning pointer member leaks when a later initialiser throws, because ~Pair never runs.
#include <cstdio>
#include <stdexcept>

struct Pair {
    int* a;
    int* b;
    Pair(bool fail) : a(new int(1)), b(nullptr) {
        if (fail) throw std::runtime_error("second allocation failed");
        b = new int(2);
    }
    ~Pair() { delete a; delete b; }
};

__attribute__((noinline)) void build() {
    try {
        Pair p(true);
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());
    }
}

int main() { build(); }
