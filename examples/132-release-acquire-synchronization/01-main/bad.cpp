// std: c++17
// sanitize: thread
// Acquire only orders what comes after the load: reading the data before the flag is checked is still a race.
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
        int copy = payload;                          // read happens before the acquire load: no synchronisation
        while (!ready.load(std::memory_order_acquire)) {}
        std::printf("payload = %d, copy = %d\n", payload, copy);
    });
    producer.join();
    consumer.join();
}
