// std: c++17
#include <cstdio>
#include <cstdlib>
#include <new>
#include <string_view>

static long allocations = 0;
void* operator new(std::size_t n) { ++allocations; if (void* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

static std::size_t total = 0;
void record(std::string_view msg) { total += msg.size(); }     // views the literal; no allocation

int main() {
    for (int i = 0; i < 1000; ++i) record("a message that is longer than the small-string buffer");
    std::printf("allocations = %ld, total = %zu\n", allocations, total);
}
