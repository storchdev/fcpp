// std: c++17
// A CAS loop is lock-free (some thread always makes progress) but not wait-free: an individual thread can retry without bound.
#include <algorithm>
#include <atomic>
#include <cstdio>
#include <thread>
#include <vector>

std::atomic<int> counter{0};

int main() {
    const int threads = 8;
    std::vector<long> retries(threads, 0);
    std::atomic<bool> go{false};
    std::vector<std::thread> pool;
    for (int t = 0; t < threads; ++t)
        pool.emplace_back([&, t] {
            while (!go.load()) {}
            for (int i = 0; i < 100000; ++i) {
                int expected = counter.load();
                while (!counter.compare_exchange_weak(expected, expected + 1)) ++retries[t];   // another thread won this round
            }
        });
    go.store(true);
    for (auto& th : pool) th.join();
    std::printf("counter = %d, worst thread retried %ld times, total retries %ld\n", counter.load(),
                *std::max_element(retries.begin(), retries.end()), [&] { long s = 0; for (long r : retries) s += r; return s; }());
}
