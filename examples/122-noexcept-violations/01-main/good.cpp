// std: c++17
#include <cstdio>
#include <stdexcept>

void parse(int x) {                                // may throw: no noexcept
    if (x < 0) throw std::invalid_argument("negative");
}

int main() {
    try {
        parse(-1);
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());
    }
}
