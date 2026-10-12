// std: c++17
#include <cstdio>
#include <optional>

std::optional<bool> read_flag() { return false; }

int main() {
    auto flag = read_flag();
    if (flag.value_or(false)) std::printf("flag is set\n");   // looks at the value, with an explicit default
    else std::printf("flag is not set\n");
}
