// std: c++17
// `auto x = {1}` deduces std::initializer_list<int>, not int.
#include <cstdio>
#include <initializer_list>
#include <type_traits>

int main() {
    auto a = {42};   // std::initializer_list<int>
    auto b{42};      // int (C++17 / N3922)
    static_assert(std::is_same_v<decltype(a), std::initializer_list<int>>);
    static_assert(std::is_same_v<decltype(b), int>);

    // Looks like a count that starts at 42, but `a` is a (pointer, size) view of a temporary array.
    std::printf("sizeof(a)=%zu sizeof(b)=%zu, a.size()=%zu\n", sizeof(a), sizeof(b), a.size());
}
