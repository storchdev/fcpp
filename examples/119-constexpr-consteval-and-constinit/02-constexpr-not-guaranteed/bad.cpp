// std: c++20
// constexpr allows compile-time evaluation but does not require it: outside a constant expression it runs at run time.
#include <cstdio>
#include <type_traits>

constexpr int where() { return std::is_constant_evaluated() ? 1 : 0; }

int main() {
    int a = where();                               // ordinary initialisation: usually run time
    constexpr int b = where();                     // constant expression: compile time
    std::printf("a = %d (1 means compile time), b = %d\n", a, b);
}
