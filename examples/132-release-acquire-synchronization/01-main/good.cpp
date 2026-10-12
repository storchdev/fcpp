// std: c++17
#include <atomic>
#include <cstdio>
#include <thread>

int payload = 0;
std::atomic<bool> ready{false};

int main() {
    std::thread producer([] {
        payload = 42;
        ready.store(true, std::memory_order_release);
    });
    std::thread consumer([] {
        while (!ready.load(std::memory_order_acquire)) {}
        int copy = payload;                          // read only after the acquire load observed the release store
        std::printf("payload = %d, copy = %d\n", payload, copy);
    });
    producer.join();
    consumer.join();
}
