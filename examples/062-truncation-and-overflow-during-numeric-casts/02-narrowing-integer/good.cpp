// std: c++17
#include <cstdio>
#include <limits>
#include <optional>
#include <vector>

std::optional<int> narrow_to_int(long long v) {
    if (v < std::numeric_limits<int>::min() || v > std::numeric_limits<int>::max()) return std::nullopt;
    return static_cast<int>(v);
}

int main(int argc, char**) {
    long long big = 3000000000LL * argc;
    auto narrowed = narrow_to_int(big);
    std::printf("narrowed has_value = %d\n", narrowed.has_value());

    int len = -argc;
    std::vector<int> v(3);
    if (len >= 0 && static_cast<std::size_t>(len) <= v.size())
        std::printf("len ok\n");
    else
        std::printf("len %d rejected\n", len);
}
