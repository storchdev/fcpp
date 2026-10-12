// std: c++17
// C++17 `new` honors over-alignment; std::aligned_alloc is the C-style equivalent.
#include <cstdio>
#include <cstdint>
#include <memory>

struct alignas(64) Block {
    char data[64];
};

int main() {
    auto b = std::make_unique<Block>();
    std::printf("aligned: %d\n", reinterpret_cast<std::uintptr_t>(b.get()) % alignof(Block) == 0);
}
