// std: c++17
#include <cstdio>

unsigned bit(unsigned n) { return n < 32 ? 1u << n : 0u; }   // decide what out-of-range means

int main(int argc, char**) {
    unsigned n = 31 + argc;
    std::printf("%u\n", bit(n));
}
