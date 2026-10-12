// std: c++17
// A call through a base pointer the compiler cannot see through stays an indirect call and cannot be inlined.
#include <chrono>
#include <cstdio>
#include <memory>

struct Shape { virtual ~Shape() = default; virtual long area(long x) const = 0; };
struct Square : Shape { long area(long x) const override { return x * x; } };

std::unique_ptr<Shape> make_shape();                // defined below, noinline so main cannot see the dynamic type
__attribute__((noinline)) std::unique_ptr<Shape> make_shape() { return std::make_unique<Square>(); }

int main() {
    auto s = make_shape();
    long sum = 0;
    auto start = std::chrono::steady_clock::now();
    for (long i = 0; i < 100000000; ++i) sum += s->area(i & 15);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("virtual through base pointer: sum = %ld, %lld ms\n", sum, (long long)ms);
}
