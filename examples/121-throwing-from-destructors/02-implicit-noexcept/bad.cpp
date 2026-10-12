// std: c++17
// Destructors are noexcept by default, so throwing from one terminates even when no other exception is active.
#include <cstdio>
#include <stdexcept>

struct File {
    ~File() { throw std::runtime_error("close failed"); }   // implicitly noexcept(true)
};

int main() {
    try {
        File f;
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());     // never reached
    }
}
