// std: c++17
// sanitize: undefined
// Placement new requires storage aligned for the type; a bump allocator that ignores alignment breaks that.
#include <cstddef>
#include <cstdio>
#include <new>

struct Arena {
    alignas(8) unsigned char buf[64];
    std::size_t used = 0;
    void* allocate(std::size_t n) { void* p = buf + used; used += n; return p; }   // no alignment
};

int main() {
    Arena arena;
    char* tag = new (arena.allocate(1)) char('x');          // used == 1 now
    double* d = new (arena.allocate(sizeof(double))) double(3.5);   // address is buf + 1: misaligned for double
    std::printf("%c %g\n", *tag, *d);
}
