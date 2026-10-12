// std: c++17
// With T = int&, `T&&` collapses to int& and `T copy = x;` declares a reference, not a copy.
#include <cstdio>
#include <type_traits>

using LR = int&;
using RR = int&&;
static_assert(std::is_same_v<LR&,  int&>);    // the only case that yields an rvalue reference is RR&&
static_assert(std::is_same_v<LR&&, int&>);
static_assert(std::is_same_v<RR&,  int&>);
static_assert(std::is_same_v<RR&&, int&&>);

template <class T>
int bump_copy(T&& x) {
    T copy = x;      // lvalue argument: T = int&, so `copy` aliases the caller's object
    ++copy;          // the "private" copy is the caller's variable
    return copy;
}

int main() {
    int n = 1;
    bump_copy(n);
    std::printf("n = %d\n", n);   // 2, not 1
}
