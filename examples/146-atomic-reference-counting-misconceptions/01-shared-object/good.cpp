// std: c++17
#include <atomic>
#include <cstdio>
#include <memory>
#include <thread>

int main() {
    auto p = std::make_shared<std::atomic<int>>(0);   // the object itself must be thread-safe
    auto work = [p] { for (int i = 0; i < 100000; ++i) p->fetch_add(1); };
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("*p = %d (expected 200000)\n", p->load());
}
