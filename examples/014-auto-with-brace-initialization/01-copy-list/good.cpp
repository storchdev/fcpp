// std: c++17
// Use `auto x = 42;` or `auto x{42};` for a single value, or name the type for a list.
#include <cstdio>
#include <initializer_list>
#include <type_traits>

int main() {
    auto a = 42;                          // int
    auto b{42};                           // int (direct-list-init, one element)
    auto c = std::initializer_list<int>{42};  // when a list is really wanted, say so
    static_assert(std::is_same_v<decltype(a), int>);
    static_assert(std::is_same_v<decltype(b), int>);
    static_assert(std::is_same_v<decltype(c), std::initializer_list<int>>);
    std::printf("%d %d %zu\n", a, b, c.size());
}
