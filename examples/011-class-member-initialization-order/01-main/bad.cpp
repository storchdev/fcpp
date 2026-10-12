// std: c++17
// sanitize: memory
// Members initialize in declaration order, not in the order of the mem-initializer list.
#include <cstddef>
#include <cstdio>
#include <memory>

class Buffer {
    std::unique_ptr<int[]> data_;   // declared FIRST -> constructed first
    std::size_t size_;              // declared second

public:
    explicit Buffer(std::size_t n)
        : size_(n),                               // written first, but runs second
          data_(std::make_unique<int[]>(size_)) {} // runs first: reads size_ before it is set!

    std::size_t size() const { return size_; }
    int* data() { return data_.get(); }
};

int main() {
    Buffer b(8);
    std::printf("size=%zu\n", b.size());
    b.data()[7] = 1;   // may overflow if size_ happened to be small
}
