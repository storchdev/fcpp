// std: c++17
// A destructor that throws while another exception is unwinding the stack calls std::terminate.
#include <cstdio>
#include <stdexcept>

struct Guard {
    ~Guard() noexcept(false) { throw std::runtime_error("cleanup failed"); }   // e.g. a flush that can fail
};

int main() {
    try {
        Guard g;
        throw std::logic_error("original error");  // unwinding destroys g, whose destructor throws
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());     // never reached
    }
}
