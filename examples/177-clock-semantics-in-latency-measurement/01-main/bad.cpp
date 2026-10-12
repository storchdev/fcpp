// std: c++17
// high_resolution_clock is an alias that may be system_clock, which can jump when the wall clock is adjusted.
#include <chrono>
#include <cstdio>
#include <type_traits>

int main() {
    using Clock = std::chrono::high_resolution_clock;
    std::printf("high_resolution_clock is steady: %d, same type as system_clock: %d, as steady_clock: %d\n",
                (int)Clock::is_steady,
                (int)std::is_same<Clock, std::chrono::system_clock>::value,
                (int)std::is_same<Clock, std::chrono::steady_clock>::value);
    auto start = Clock::now();                      // not monotonic if it is the system clock
    auto end = Clock::now();
    long long ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::printf("elapsed is non-negative here: %d (not guaranteed for a non-steady clock)\n", (int)(ns >= 0));
}
