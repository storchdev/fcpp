// std: c++20
#include <atomic>
#include <cstdio>
#include <thread>

int counter = 0;

int main() {
    auto work = [] { std::atomic_ref<int> r(counter); for (int i = 0; i < 100000; ++i) r.fetch_add(1); };   // every access is atomic
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("counter = %d (expected 200000)\n", counter);
}
