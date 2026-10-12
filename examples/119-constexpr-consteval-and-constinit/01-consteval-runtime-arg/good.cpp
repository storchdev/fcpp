// std: c++20
#include <cstdio>

consteval int square(int n) { return n * n; }

int main() {
    constexpr int n = 5;
    std::printf("%d\n", square(n));
}
