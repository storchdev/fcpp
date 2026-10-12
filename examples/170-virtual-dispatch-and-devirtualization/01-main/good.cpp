// std: c++17
#include <chrono>
#include <cstdio>

struct Shape { virtual ~Shape() = default; virtual long area(long x) const = 0; };
struct Square final : Shape { long area(long x) const override { return x * x; } };   // final: calls on a Square are direct

int main() {
    Square sq;
    long sum = 0;
    auto start = std::chrono::steady_clock::now();
    for (long i = 0; i < 100000000; ++i) sum += sq.area(i & 15);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("direct call on final type: sum = %ld, %lld ms\n", sum, (long long)ms);
}
