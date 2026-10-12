// std: c++17
#include <atomic>
#include <cstdio>
#include <thread>

std::atomic<int> counter{0};
std::atomic<bool> ready{false};
int payload = 0;                     // non-atomic, but published via the release/acquire pair below

int main() {
    std::thread producer([] {
        payload = 42;
        ready.store(true, std::memory_order_release);   // publishes payload
    });
    std::thread incrementer([] {
        for (int i = 0; i < 100000; ++i) counter.fetch_add(1, std::memory_order_relaxed);
    });
    for (int i = 0; i < 100000; ++i) counter.fetch_add(1, std::memory_order_relaxed);

    while (!ready.load(std::memory_order_acquire)) {}   // synchronizes-with the store
    std::printf("payload=%d\n", payload);

    producer.join();
    incrementer.join();
    std::printf("counter=%d (expected 200000)\n", counter.load());
}
