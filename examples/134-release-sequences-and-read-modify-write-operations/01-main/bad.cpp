// std: c++17
// A plain store by another thread ends the release sequence, so the acquire load no longer synchronises with the producer.
#include <atomic>
#include <cstdio>
#include <thread>

int payload = 0;
std::atomic<int> state{0};

int main() {
    std::thread producer([] {
        payload = 42;
        state.store(1, std::memory_order_release);
    });
    std::thread relay([] {
        while (state.load(std::memory_order_relaxed) != 1) {}
        state.store(2, std::memory_order_relaxed);   // not a read-modify-write: breaks the release sequence
    });
    std::thread consumer([] {
        while (state.load(std::memory_order_acquire) != 2) {}
        std::printf("payload = %d\n", payload);      // race with the producer's write
    });
    producer.join();
    relay.join();
    consumer.join();
}
