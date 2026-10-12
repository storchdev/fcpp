// std: c++17
#include <climits>
#include <cstdio>
#include <optional>

std::optional<int> divide(int a, int b) {
    if (b == 0 || (a == INT_MIN && b == -1)) return std::nullopt;   // the only two failing inputs
    return a / b;
}

int main(int argc, char**) {
    int minus_one = -argc;
    auto r = divide(INT_MIN, minus_one);
    std::printf("has_value = %d\n", r.has_value());
}
