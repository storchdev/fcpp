// std: c++17
// Say what conversion you mean; brace-init then only accepts conversions that cannot lose information.
#include <cmath>
#include <cstdint>
#include <cstdio>

int main() {
    std::uint8_t level{200};                         // constant that fits: fine
    int whole{static_cast<int>(std::lround(3.5))};   // explicit, and rounds instead of truncating
    int widened{level};                              // uint8_t -> int never loses information
    std::printf("%d %d %d\n", level, whole, widened);
}
