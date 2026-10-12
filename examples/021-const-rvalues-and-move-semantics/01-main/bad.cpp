// std: c++17
// std::move(const T) yields `const T&&`, which cannot bind to `T&&`, so the copy constructor runs.
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
    const Blob original("0123456789012345678901234567890123456789");
    static_assert(std::is_same_v<decltype(std::move(original)), const Blob&&>);

    Blob taken = std::move(original);   // prints "copy": const Blob&& binds only to const Blob&
    std::printf("original still holds %zu bytes\n", original.data.size());
    (void)taken;
}
