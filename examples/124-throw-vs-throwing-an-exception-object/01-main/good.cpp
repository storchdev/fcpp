// std: c++17
#include <cstdio>
#include <exception>

struct DiskError : std::exception {
    const char* what() const noexcept override { return "disk full"; }
};

void middle() {
    try {
        throw DiskError{};
    } catch (const std::exception& e) {
        std::printf("middle saw: %s\n", e.what());
        throw;                                     // rethrows the active exception object, dynamic type intact
    }
}

int main() {
    try {
        middle();
    } catch (const DiskError&) {
        std::printf("outer: DiskError\n");
    } catch (const std::exception& e) {
        std::printf("outer: plain exception, what() = %s\n", e.what());
    }
}
