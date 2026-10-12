// std: c++17
// A non-explicit operator bool lets handles take part in arithmetic and comparisons as bools.
#include <cstdio>

struct Handle {
    int fd;
    operator bool() const { return fd >= 0; }   // missing `explicit`
};

int main() {
    Handle a{3}, b{7};
    if (a == b)                          // compiles: both converted to bool, true == true
        std::puts("a == b (different descriptors!)");
    int open_count = a + b;              // compiles: 1 + 1
    std::printf("open_count=%d\n", open_count);
}
