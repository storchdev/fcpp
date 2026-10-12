// std: c++17
#include <cstdio>
#include <optional>

std::optional<int> to_int(double d) {
    if (!(d > -2147483649.0 && d < 2147483648.0)) return std::nullopt;   // also rejects NaN
    return static_cast<int>(d);
}

int main(int argc, char**) {
    double big = 1e10 * argc;
    auto r = to_int(big);
    std::printf("has_value = %d\n", r.has_value());
}
