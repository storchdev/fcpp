// std: c++17
#include <cstdio>
#include <memory>
#include <stdexcept>

struct Pair {
    std::unique_ptr<int> a;
    std::unique_ptr<int> b;
    Pair(bool fail) : a(new int(1)) {
        if (fail) throw std::runtime_error("second allocation failed");
        b.reset(new int(2));
    }
};

__attribute__((noinline)) void build() {
    try {
        Pair p(true);
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());
    }
}

int main() { build(); }
