// std: c++20
// Strip the reference (and cv) from T before declaring a value.
#include <cstdio>
#include <type_traits>

template <class T>
int bump_copy(T&& x) {
    std::remove_cvref_t<T> copy = x;   // always a value type
    ++copy;
    return copy;
}

int main() {
    int n = 1;
    bump_copy(n);
    std::printf("n = %d\n", n);   // 1
}
