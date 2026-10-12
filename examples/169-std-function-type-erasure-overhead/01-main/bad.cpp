// std: c++17
// A std::function holding a callable too large for its small-object buffer allocates when it is constructed.
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <new>

static long allocations = 0;
void* operator new(std::size_t n) { ++allocations; if (void* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

struct Big { long a, b, c, d; };

long apply(const std::function<long()>& f) { return f(); }

int main() {
    Big big{1, 2, 3, 4};
    long sum = 0;
    for (int i = 0; i < 1000; ++i) sum += apply([big] { return big.a + big.d; });   // converts the lambda to a std::function each call
    std::printf("allocations = %ld, sum = %ld, sizeof(std::function) = %zu\n", allocations, sum, sizeof(std::function<long()>));
}
