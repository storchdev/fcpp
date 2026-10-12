// std: c++17
// A deferred task does not run until get()/wait(): polling with wait_for never sees it become ready.
#include <chrono>
#include <cstdio>
#include <future>

int main() {
    auto f = std::async(std::launch::deferred, [] { return 7; });
    int polls = 0;
    while (f.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready && polls < 5) ++polls;   // would spin forever without the cap
    std::printf("polls = %d, status is deferred: %d\n", polls, (int)(f.wait_for(std::chrono::seconds(0)) == std::future_status::deferred));
}
