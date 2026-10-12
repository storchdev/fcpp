// std: c++17
#include <atomic>
#include <cstdio>

int main() {
    std::atomic<int> x{0};
    int expected = 0;
    bool ok = x.compare_exchange_strong(expected, 1, std::memory_order_acq_rel, std::memory_order_acquire);   // failure is a load: acquire/relaxed/seq_cst
    std::printf("ok = %d\n", (int)ok);
}
