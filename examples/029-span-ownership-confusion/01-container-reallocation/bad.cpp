// std: c++20
// sanitize: address
// A span holds a pointer and size; growing the vector reallocates and leaves the span pointing at freed memory.
#include <cstdio>
#include <span>
#include <vector>

int main() {
    std::vector<int> v(4, 7);
    std::span<int> view(v);          // pointer to v's current buffer
    v.resize(1000);                  // reallocates: the old buffer is freed
    std::printf("%d\n", view[0]);    // UB: heap-use-after-free
}
