// std: c++17
// sanitize: thread
// Two code paths take the same two mutexes in opposite orders: a deadlock waiting for the right interleaving.
#include <cstdio>
#include <mutex>
#include <thread>

std::mutex a, b;

int main() {
    std::thread t1([] { std::lock_guard<std::mutex> x(a); std::lock_guard<std::mutex> y(b); });   // a then b
    t1.join();
    std::thread t2([] { std::lock_guard<std::mutex> x(b); std::lock_guard<std::mutex> y(a); });   // b then a
    t2.join();
    std::printf("finished (run sequentially here, but concurrent runs can deadlock)\n");
}
