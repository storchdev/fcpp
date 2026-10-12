// std: c++20
// sanitize: thread
// While any atomic_ref refers to an object, all concurrent accesses must go through atomic_refs: a plain access races.
#include <atomic>
#include <cstdio>
#include <thread>

int counter = 0;

int main() {
    std::thread a([] { std::atomic_ref<int> r(counter); for (int i = 0; i < 100000; ++i) r.fetch_add(1); });
    std::thread b([] { for (int i = 0; i < 100000; ++i) ++counter; });   // plain increment of the same object
    a.join();
    b.join();
    std::printf("counter = %d (expected 200000)\n", counter);
}
