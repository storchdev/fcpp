// std: c++17
#include <cstdio>
#include <stdexcept>

struct Guard {
    ~Guard() {
        try { throw std::runtime_error("cleanup failed"); }   // handle failures inside the destructor
        catch (const std::exception& e) { std::printf("cleanup error logged: %s\n", e.what()); }
    }
};

int main() {
    try {
        Guard g;
        throw std::logic_error("original error");
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());
    }
}
