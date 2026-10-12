// std: c++17
#include <cstdio>
#include <utility>

struct Buffer {
    int* data;
    Buffer() : data(new int[4]{1, 2, 3, 4}) {}
    Buffer(const Buffer&) = delete;
    Buffer& operator=(Buffer&& o) noexcept {
        if (this != &o) {                      // a self-move now leaves the object unchanged
            delete[] data;
            data = o.data;
            o.data = nullptr;
        }
        return *this;
    }
    ~Buffer() { delete[] data; }
};

template <class T> void assign(T& dst, T& src) { dst = std::move(src); }

int main() {
    Buffer b;
    assign(b, b);
    std::printf("Buffer: data is %s\n", b.data ? "set" : "null");
}
