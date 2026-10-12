// std: c++17
// expect: compile-error
// g++ 16: error: narrowing conversion of '300' from 'int' to 'uint8_t' {aka 'unsigned char'} [-Wnarrowing]
// clang++ 23: error: constant expression evaluates to 300 which cannot be narrowed to type 'std::uint8_t' [-Wc++11-narrowing]
#include <cstdint>
#include <cstdio>

int main() {
    std::uint8_t level{300};   // ill-formed: 300 does not fit in uint8_t
    int whole{3.5};            // ill-formed: double -> int is narrowing
    std::printf("%d %d\n", level, whole);
}
