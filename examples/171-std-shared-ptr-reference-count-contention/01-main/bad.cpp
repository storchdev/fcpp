// std: c++17
// Passing shared_ptr by value from several threads makes them all hammer the same atomic reference count.
#include <atomic>
#include <chrono>
#include <cstdio>
#include <memory>
#include <thread>
#include <vector>

struct Config { std::atomic<int> value{1}; };

__attribute__((noinline)) int read_value(std::shared_ptr<Config> c) { return c->value.load(std::memory_order_relaxed); }   // by value: two atomic ops per call

int main() {
    auto cfg = std::make_shared<Config>();
    std::atomic<bool> go{false};
    std::atomic<long> total{0};
    std::vector<std::thread> pool;
    for (int t = 0; t < 4; ++t)
        pool.emplace_back([&] {
            while (!go.load()) {}
            long sum = 0;
            for (int i = 0; i < 5000000; ++i) sum += read_value(cfg);
            total += sum;
        });
    auto start = std::chrono::steady_clock::now();
    go.store(true);
    for (auto& th : pool) th.join();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("shared_ptr by value: total = %ld, %lld ms\n", total.load(), (long long)ms);
}
