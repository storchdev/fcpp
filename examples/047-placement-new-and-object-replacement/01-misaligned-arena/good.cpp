// std: c++17
// Round the offset up to the type's alignment before constructing.
#include <cstddef>
#include <cstdio>
#include <new>

struct Arena {
    alignas(8) unsigned char buf[64];
    std::size_t used = 0;
    void* allocate(std::size_t n, std::size_t align) {
        used = (used + align - 1) & ~(align - 1);
        void* p = buf + used;
        used += n;
        return p;
    }
};

int main() {
    Arena arena;
    char* tag = new (arena.allocate(1, alignof(char))) char('x');
    double* d = new (arena.allocate(sizeof(double), alignof(double))) double(3.5);
    std::printf("%c %g\n", *tag, *d);
}
