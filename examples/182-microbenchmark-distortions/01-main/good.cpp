// std: c++17
#include <chrono>
#include <cstdio>

int main() {
    auto start = std::chrono::steady_clock::now();
    long sum = 0;
    for (long i = 0; i < 1000000000; ++i) {
        sum += i * 3 + 1;
        asm volatile("" : "+r"(sum));               // optimization barrier: the compiler must keep each partial sum
    }
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("1000000000 iterations took %lld ns (sum = %ld)\n", (long long)ns, sum);
}
