// std: c++20
// Outside braces, the same narrowing conversions are accepted (g++ warns about the constant 300 only).
#include <cstdint>
#include <cstdio>

int main() {
    double ratio = 99.9;
    int percent = ratio;                  // truncates to 99, not 100
    std::uint8_t level = 300;             // wraps modulo 256
    std::int64_t big = 5'000'000'000;
    std::int32_t id = big;                // keeps the low 32 bits
    float f = 16777217;                   // 2^24 + 1 is not representable as float

    std::printf("percent=%d level=%d id=%d f=%.1f\n", percent, level, id, f);
}
