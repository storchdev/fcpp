// std: c++17
#include <cstdio>
#include <exception>

struct DiskError : std::exception {
    const char* what() const noexcept override { return "disk full"; }
};

int main() {
    try {
        throw DiskError{};
    } catch (const std::exception& e) {            // by reference: no copy, no slicing
        std::printf("what() = %s\n", e.what());
    }
}
