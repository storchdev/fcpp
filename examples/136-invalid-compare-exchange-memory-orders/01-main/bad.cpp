// std: c++17
// The failure order of compare_exchange is a load, so it may not be release or acq_rel.
#include <atomic>
#include <cstdio>

int main() {
    std::atomic<int> x{0};
    int expected = 0;
    bool ok = x.compare_exchange_strong(expected, 1, std::memory_order_acq_rel, std::memory_order_release);   // invalid failure order
    std::printf("ok = %d\n", (int)ok);
}
