// std: c++17
#include <cstdio>
#include <optional>

std::optional<int> average(int total, int count) {
    if (count == 0) return std::nullopt;
    return total / count;
}

int main(int argc, char**) {
    int count = argc - 1;
    auto r = average(10, count);
    std::printf("has_value = %d\n", r.has_value());
}
