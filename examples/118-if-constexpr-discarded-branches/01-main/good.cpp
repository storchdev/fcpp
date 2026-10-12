// std: c++17
#include <cstdio>
#include <type_traits>

template <class T>
void show(T v) {
    if constexpr (std::is_integral_v<T>) {
        std::printf("int %lld\n", (long long)v);
    } else {
        v.print();                                 // dependent on T: only checked when this branch is instantiated
    }
}

int main() { show(5); }
