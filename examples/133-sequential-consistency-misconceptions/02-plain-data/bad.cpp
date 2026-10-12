// std: c++17
// sanitize: thread
// seq_cst orders atomic operations; it does not make the plain variables around them safe to share.
#include <atomic>
#include <cstdio>
#include <thread>

std::atomic<int> turn{0};                          // seq_cst by default
int shared_total = 0;                              // plain

int main() {
    auto work = [] { turn.fetch_add(1); ++shared_total; };   // the atomic does not guard the plain increment
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("turn = %d, shared_total = %d\n", turn.load(), shared_total);
}
