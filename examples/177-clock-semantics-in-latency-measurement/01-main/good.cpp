// std: c++17
#include <chrono>
#include <cstdio>

int main() {
    using Clock = std::chrono::steady_clock;
    static_assert(Clock::is_steady, "steady_clock is guaranteed monotonic");
    auto start = Clock::now();
    auto end = Clock::now();
    std::printf("steady_clock is steady: %d, non-negative elapsed: %d\n", (int)Clock::is_steady, (int)((end - start).count() >= 0));
}
