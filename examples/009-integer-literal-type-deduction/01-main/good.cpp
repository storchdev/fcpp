// std: c++17
// Use fixed-width types and explicit suffixes, and compare values of the same signedness.
#include <cstdint>
#include <cstdio>

int main() {
    constexpr std::uint32_t mask = 0xFFFFFFFFu;     // the suffix says what you mean
    constexpr std::int64_t big = 2147483648LL;

    int status = -1;
    if (static_cast<std::int64_t>(status) < static_cast<std::int64_t>(mask)) std::puts("-1 < 0xFFFFFFFF");
    std::printf("big=%lld mask=%u\n", static_cast<long long>(big), mask);
}
