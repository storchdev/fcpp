// std: c++20
#include <cstdio>

consteval int where() { return 1; }                // consteval: every call is evaluated at compile time

int main() {
    int a = where();
    std::printf("a = %d\n", a);
}
