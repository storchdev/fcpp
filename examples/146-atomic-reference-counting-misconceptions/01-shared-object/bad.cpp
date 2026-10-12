// std: c++17
// sanitize: thread
// The reference count is atomic, but the pointee is not: two threads mutating *p through their own copies race.
#include <cstdio>
#include <memory>
#include <thread>

int main() {
    auto p = std::make_shared<int>(0);
    auto work = [p] { for (int i = 0; i < 100000; ++i) ++*p; };   // each thread owns a copy of the shared_ptr
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("*p = %d (expected 200000)\n", *p);
}
