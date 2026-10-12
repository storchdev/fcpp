// std: c++17
// sanitize: undefined
// malloc only guarantees alignof(max_align_t); an alignas(64) object needs aligned allocation.
#include <cstdio>
#include <cstdlib>
#include <new>

struct alignas(64) Block {
    char data[64];
};

int main() {
    void* first = std::malloc(24);                       // other allocations shift where the next one lands
    void* mem = std::malloc(sizeof(Block));              // 16-byte aligned at best
    Block* b = new (mem) Block{};                        // UB unless mem happens to be 64-byte aligned
    std::printf("%p\n", static_cast<void*>(b->data));
    std::free(b);
    std::free(first);
}
