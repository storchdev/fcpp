// std: c++17
// An exception that leaves a noexcept function calls std::terminate instead of propagating.
#include <cstdio>
#include <stdexcept>

void parse(int x) noexcept {
    if (x < 0) throw std::invalid_argument("negative");   // promised not to throw
}

int main() {
    try {
        parse(-1);
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());     // never reached
    }
}
