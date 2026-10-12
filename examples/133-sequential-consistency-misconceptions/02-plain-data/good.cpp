// std: c++17
#include <atomic>
#include <cstdio>
#include <thread>

std::atomic<int> turn{0};
std::atomic<int> shared_total{0};                  // the shared data itself is atomic

int main() {
    auto work = [] { turn.fetch_add(1); shared_total.fetch_add(1); };
    std::thread a(work), b(work);
    a.join();
    b.join();
    std::printf("turn = %d, shared_total = %d\n", turn.load(), shared_total.load());
}
