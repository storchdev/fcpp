// std: c++17
// Each atomic operation is indivisible, but a load followed by a store is two operations: updates can be lost.
#include <atomic>
#include <cstdio>
#include <thread>

int main() {
    std::atomic<int> counter{0};
    auto work = [&] { for (int i = 0; i < 100000; ++i) counter.store(counter.load() + 1); };   // not one atomic step
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("counter = %d (expected 200000)\n", counter.load());
}
