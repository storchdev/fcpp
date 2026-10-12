// std: c++17
// `throw e;` throws a copy of the static type of e; `throw;` rethrows the original exception object.
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
        throw e;                                   // copy-initialises a std::exception: slices
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
