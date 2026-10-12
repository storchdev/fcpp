// std: c++17
#include <cstdio>
#include <utility>

struct Buffer {
    Buffer() = default;
    Buffer(const Buffer&) { std::puts("copy"); }
    Buffer(Buffer&&) noexcept { std::puts("move"); }
};

int main() {
    Buffer a;                                  // drop const from the object that is meant to be moved from
    Buffer b = std::move(a);                   // prints "move"
    (void)b;
}
