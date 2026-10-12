// std: c++17
// explicit operator bool still works wherever the language asks for a condition.
#include <cstdio>

struct Handle {
    int fd;
    explicit operator bool() const { return fd >= 0; }
    friend bool operator==(Handle l, Handle r) { return l.fd == r.fd; }
};

int main() {
    Handle a{3}, b{7};
    if (a == b) std::puts("same descriptor");           // now compares descriptors
    if (a && !Handle{-1}) std::puts("contextual conversions: if, &&, ||, !, ?:, while");
    bool ok = static_cast<bool>(a);                     // explicit request
    // bool bad = a;                                    // error: copy-initialization needs an implicit conversion
    // int n = a + b;                                   // error: no implicit conversion to arithmetic type
    std::printf("ok=%d\n", ok);
}
