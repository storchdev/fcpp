// std: c++17
// A self-move-assignment is valid but leaves the object in an unspecified state: here the data is silently lost.
#include <cstdio>
#include <utility>
#include <vector>

struct Buffer {
    int* data;
    Buffer() : data(new int[4]{1, 2, 3, 4}) {}
    Buffer(const Buffer&) = delete;
    Buffer& operator=(Buffer&& o) noexcept {
        delete[] data;                         // if &o == this, this frees the data we are about to steal
        data = o.data;
        o.data = nullptr;
        return *this;
    }
    ~Buffer() { delete[] data; }
};

template <class T> void assign(T& dst, T& src) { dst = std::move(src); }   // callers may pass the same object

int main() {
    Buffer b;
    assign(b, b);
    std::printf("Buffer: data is %s\n", b.data ? "set" : "null");

    std::vector<int> v{1, 2, 3};
    assign(v, v);
    std::printf("vector: size=%zu\n", v.size());
}
