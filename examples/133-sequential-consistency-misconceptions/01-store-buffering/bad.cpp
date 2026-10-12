// std: c++17
// Release/acquire does not forbid both threads from missing each other's store; only seq_cst gives a single total order.
#include <atomic>
#include <cstdio>
#include <thread>

std::atomic<int> x, y, round_go{-1}, done{0};
constexpr int N = 200000;
int r1[N], r2[N];

int main() {
    auto worker = [](bool first) {
        for (int i = 0; i < N; ++i) {
            while (round_go.load(std::memory_order_acquire) < i) {}      // wait for the round to start
            if (first) { x.store(1, std::memory_order_release); r1[i] = y.load(std::memory_order_acquire); }
            else       { y.store(1, std::memory_order_release); r2[i] = x.load(std::memory_order_acquire); }
            done.fetch_add(1, std::memory_order_acq_rel);
        }
    };
    std::thread a(worker, true), b(worker, false);
    int both_zero = 0;
    for (int i = 0; i < N; ++i) {
        x.store(0, std::memory_order_relaxed); y.store(0, std::memory_order_relaxed);
        done.store(0, std::memory_order_release);
        round_go.store(i, std::memory_order_release);
        while (done.load(std::memory_order_acquire) < 2) {}
        if (r1[i] == 0 && r2[i] == 0) ++both_zero;
    }
    a.join();
    b.join();
    std::printf("both loads saw 0 in %d of %d rounds\n", both_zero, N);
}
