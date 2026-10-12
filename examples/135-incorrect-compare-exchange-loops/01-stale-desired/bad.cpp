// std: c++17
// compare_exchange refreshes `expected` on failure, but a `desired` computed before the loop is not refreshed.
#include <atomic>
#include <cstdio>
#include <thread>

std::atomic<int> counter{0};

void add_one() {
    int expected = counter.load();
    int desired = expected + 1;                     // computed once
    while (!counter.compare_exchange_weak(expected, desired)) {}   // on failure expected is current, desired is stale
}

int main() {
    std::thread a([] { for (int i = 0; i < 100000; ++i) add_one(); });
    std::thread b([] { for (int i = 0; i < 100000; ++i) add_one(); });
    a.join();
    b.join();
    std::printf("counter = %d (expected 200000)\n", counter.load());
}
