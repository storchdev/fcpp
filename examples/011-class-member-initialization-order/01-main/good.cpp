// std: c++17
#include <cstddef>
#include <cstdio>
#include <memory>

class Buffer {
    std::size_t size_;              // declare dependencies BEFORE what uses them
    std::unique_ptr<int[]> data_;

public:
    explicit Buffer(std::size_t n)
        : size_(n),
          data_(std::make_unique<int[]>(n)) {}   // and prefer the parameter over a sibling member

    std::size_t size() const { return size_; }
    int* data() { return data_.get(); }
};

int main() {
    Buffer b(8);
    b.data()[7] = 1;
    std::printf("size=%zu last=%d\n", b.size(), b.data()[7]);
}
