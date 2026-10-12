// std: c++17
// std::move on a const object yields const T&&, which cannot bind to T&&: the copy constructor runs.
#include <cstdio>
#include <utility>

struct Buffer {
    Buffer() = default;
    Buffer(const Buffer&) { std::puts("copy"); }
    Buffer(Buffer&&) noexcept { std::puts("move"); }
};

int main() {
    const Buffer a;
    Buffer b = std::move(a);                   // prints "copy"
    Buffer c;
    Buffer d = std::move(c);                   // prints "move"
    (void)b; (void)d;
}
