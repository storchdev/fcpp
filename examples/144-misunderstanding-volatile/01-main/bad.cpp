// std: c++17
// sanitize: thread
// volatile prevents the compiler from caching a value, but gives no atomicity or ordering between threads.
#include <cstdio>
#include <thread>

volatile int counter = 0;

int main() {
    auto work = [] { for (int i = 0; i < 100000; ++i) counter = counter + 1; };
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("counter = %d (expected 200000)\n", counter);
}
