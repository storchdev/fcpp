// std: c++17
// `if (opt)` tests whether the optional holds a value, not whether that value is truthy.
#include <cstdio>
#include <optional>

std::optional<bool> read_flag() { return false; }   // present, and false

int main() {
    auto flag = read_flag();
    if (flag) std::printf("flag is set\n");         // true: the optional is engaged, even though the bool is false
    else std::printf("flag is not set\n");
}
