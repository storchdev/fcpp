// std: c++17
#include <atomic>
#include <cstdio>
#include <thread>

int payload = 0;
std::atomic<bool> ready{false};

int main() {
    std::thread producer([] {
        payload = 42;
        ready.store(true, std::memory_order_release);   // publishes everything written before it
    });
    std::thread consumer([] {
        while (!ready.load(std::memory_order_acquire)) {}   // synchronises with the release store
        std::printf("payload = %d\n", payload);
    });
    producer.join();
    consumer.join();
}
