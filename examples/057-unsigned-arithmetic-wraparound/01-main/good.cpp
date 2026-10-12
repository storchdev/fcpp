// std: c++17
#include <cstdio>
#include <optional>
#include <vector>

std::optional<std::size_t> last_index(const std::vector<int>& v) {
    if (v.empty()) return std::nullopt;     // test before subtracting
    return v.size() - 1;
}

int main() {
    std::vector<int> empty;
    auto idx = last_index(empty);
    std::printf("last_index(empty) has_value = %d\n", idx.has_value());

    for (unsigned i = 4; i-- > 0;)          // runs i = 3, 2, 1, 0 and stops
        std::printf("i = %u\n", i);
}
