// std: c++17
// Catching by value copies only the base subobject: the derived type and its overrides are lost.
#include <cstdio>
#include <exception>

struct DiskError : std::exception {
    const char* what() const noexcept override { return "disk full"; }
};

int main() {
    try {
        throw DiskError{};
    } catch (std::exception e) {                   // slices DiskError to std::exception
        std::printf("what() = %s\n", e.what());
    }
}
