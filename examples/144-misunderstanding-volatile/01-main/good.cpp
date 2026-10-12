// std: c++17
#include <atomic>
#include <cstdio>
#include <thread>

std::atomic<int> counter{0};

int main() {
    auto work = [] { for (int i = 0; i < 100000; ++i) counter.fetch_add(1); };
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("counter = %d (expected 200000)\n", counter.load());
}
