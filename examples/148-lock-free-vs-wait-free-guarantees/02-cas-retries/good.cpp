// std: c++17
#include <atomic>
#include <cstdio>
#include <thread>
#include <vector>

std::atomic<int> counter{0};

int main() {
    const int threads = 8;
    std::atomic<bool> go{false};
    std::vector<std::thread> pool;
    for (int t = 0; t < threads; ++t)
        pool.emplace_back([&] {
            while (!go.load()) {}
            for (int i = 0; i < 100000; ++i) counter.fetch_add(1);   // a single RMW with no retry loop in the source
        });
    go.store(true);
    for (auto& th : pool) th.join();
    std::printf("counter = %d, no retries in the source\n", counter.load());
}
