// std: c++17
// Passing a string literal to a `std::string` parameter allocates (for text beyond the small-string buffer) on every call.
#include <cstdio>
#include <cstdlib>
#include <new>
#include <string>

static long allocations = 0;
void* operator new(std::size_t n) { ++allocations; if (void* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

static std::size_t total = 0;
void record(const std::string& msg) { total += msg.size(); }   // only reads the text

int main() {
    for (int i = 0; i < 1000; ++i) record("a message that is longer than the small-string buffer");   // builds a std::string each call
    std::printf("allocations = %ld, total = %zu\n", allocations, total);
}
