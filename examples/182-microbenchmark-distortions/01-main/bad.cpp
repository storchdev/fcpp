// std: c++17
// A loop whose result is never used can be deleted by the optimizer, so the "benchmark" measures nothing.
#include <chrono>
#include <cstdio>

int main() {
    auto start = std::chrono::steady_clock::now();
    long sum = 0;
    for (long i = 0; i < 1000000000; ++i) sum += i * 3 + 1;   // sum is never read
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("1000000000 iterations took %lld ns\n", (long long)ns);
}
