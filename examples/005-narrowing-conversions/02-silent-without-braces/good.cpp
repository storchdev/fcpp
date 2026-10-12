// std: c++20
// Use brace-init so the compiler rejects lossy conversions, and check ranges for runtime values.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <utility>

int main() {
    double ratio = 99.9;
    int percent{static_cast<int>(std::lround(ratio))};   // 100, and the cast is visible

    int raw = 300;
    if (std::in_range<std::uint8_t>(raw)) {
        std::uint8_t level{static_cast<std::uint8_t>(raw)};
        std::printf("level=%d\n", level);
    } else {
        std::puts("300 does not fit in uint8_t");
    }

    std::int64_t big = 5'000'000'000;
    std::printf("percent=%d fits_in_int32=%d\n", percent, std::in_range<std::int32_t>(big));
}
