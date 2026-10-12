// std: c++17
// sanitize: thread
// Two threads, unsynchronized conflicting accesses: a data race, therefore UB.
#include <cstdio>
#include <thread>

int counter = 0;
bool ready = false;     // plain bool used as a flag
int payload = 0;

int main() {
    std::thread producer([] {
        payload = 42;
        ready = true;                 // no happens-before edge to the consumer
    });
    std::thread incrementer([] {
        for (int i = 0; i < 100000; ++i) ++counter;   // racing with the other thread
    });
    for (int i = 0; i < 100000; ++i) ++counter;

    while (!ready) {}                 // compiler may hoist the load: infinite loop
    std::printf("payload=%d\n", payload);

    producer.join();
    incrementer.join();
    std::printf("counter=%d (expected 200000)\n", counter);
}
