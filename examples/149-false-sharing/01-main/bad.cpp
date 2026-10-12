// std: c++17
// Two threads update different counters that share a cache line: no data race, but the line ping-pongs between cores.
#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>

struct Counters { std::atomic<long> a{0}; std::atomic<long> b{0}; };   // adjacent: same cache line

int main() {
    Counters c;
    std::atomic<bool> go{false};
    std::thread t1([&] { while (!go.load()) {} for (long i = 0; i < 50000000; ++i) c.a.fetch_add(1, std::memory_order_relaxed); });
    std::thread t2([&] { while (!go.load()) {} for (long i = 0; i < 50000000; ++i) c.b.fetch_add(1, std::memory_order_relaxed); });
    auto start = std::chrono::steady_clock::now();
    go.store(true);
    t1.join();
    t2.join();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("adjacent counters: %lld ms\n", (long long)ms);
}
