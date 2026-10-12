// std: c++17
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <new>

static long allocations = 0;
void* operator new(std::size_t n) { ++allocations; if (void* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

struct Big { long a, b, c, d; };

template <class F> long apply(F&& f) { return f(); }           // the callable's type is kept: no erasure, no allocation

int main() {
    Big big{1, 2, 3, 4};
    long sum = 0;
    for (int i = 0; i < 1000; ++i) sum += apply([big] { return big.a + big.d; });
    std::printf("allocations = %ld, sum = %ld, sizeof(std::function) = %zu\n", allocations, sum, sizeof(std::function<long()>));
}
