// std: c++17
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
        int expected = 1;
        while (!state.compare_exchange_weak(expected, 2, std::memory_order_relaxed)) expected = 1;   // an RMW continues the release sequence
    });
    std::thread consumer([] {
        while (state.load(std::memory_order_acquire) != 2) {}
        std::printf("payload = %d\n", payload);
    });
    producer.join();
    relay.join();
    consumer.join();
}
