// std: c++17
#include <atomic>
#include <cstdio>
#include <thread>

std::atomic<int> counter{0};

void add_one() {
    int expected = counter.load();
    while (!counter.compare_exchange_weak(expected, expected + 1)) {}   // desired is recomputed from the refreshed expected
}

int main() {
    std::thread a([] { for (int i = 0; i < 100000; ++i) add_one(); });
    std::thread b([] { for (int i = 0; i < 100000; ++i) add_one(); });
    a.join();
    b.join();
    std::printf("counter = %d (expected 200000)\n", counter.load());
}
