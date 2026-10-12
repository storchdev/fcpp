// std: c++17
// Integer conversions never trap: they wrap, change sign, or (before C++20) are implementation-defined.
#include <cstdio>
#include <vector>

int main(int argc, char**) {
    long long big = 3000000000LL * argc;
    int narrowed = big;                        // out of int range: implementation-defined before C++20
    std::printf("narrowed = %d\n", narrowed);

    int len = -argc;                           // -1
    std::vector<int> v(3);
    std::size_t n = len;                       // negative -> huge size_t
    std::printf("n = %zu, n > v.size() = %d\n", n, n > v.size());

    unsigned char c = 300 * argc;              // wraps modulo 256 (defined)
    std::printf("c = %d\n", c);
}
