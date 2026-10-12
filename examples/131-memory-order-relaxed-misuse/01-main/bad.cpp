// std: c++17
// sanitize: thread
// A relaxed store/load pair is atomic but does not make the earlier plain write visible to the reader.
#include <atomic>
#include <cstdio>
#include <thread>

int payload = 0;
std::atomic<bool> ready{false};

int main() {
    std::thread producer([] {
        payload = 42;
        ready.store(true, std::memory_order_relaxed);   // no release: payload is not published
    });
    std::thread consumer([] {
        while (!ready.load(std::memory_order_relaxed)) {}   // no acquire
        std::printf("payload = %d\n", payload);          // data race with the write above
    });
    producer.join();
    consumer.join();
}
