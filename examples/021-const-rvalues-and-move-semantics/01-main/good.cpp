// std: c++17
// Don't declare locals const when you intend to move from them; const is for things that stay put.
#include <cstdio>
#include <string>
#include <type_traits>
#include <utility>

struct Blob {
    std::string data;
    explicit Blob(std::string s) : data(std::move(s)) {}
    Blob(const Blob& o) : data(o.data) { std::puts("copy"); }
    Blob(Blob&& o) noexcept : data(std::move(o.data)) { std::puts("move"); }
};

int main() {
    Blob original("0123456789012345678901234567890123456789");
    static_assert(std::is_same_v<decltype(std::move(original)), Blob&&>);

    Blob taken = std::move(original);   // prints "move"
    std::printf("original now holds %zu bytes\n", original.data.size());
    (void)taken;
}
