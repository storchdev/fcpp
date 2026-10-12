// std: c++17
// A pointer to freed memory is invalid even if a new allocation gets the same address.
#include <cstdio>
#include <cstdlib>

int main() {
    int* p = static_cast<int*>(std::malloc(sizeof(int)));
    *p = 1;
    std::free(p);                                          // p now has an invalid pointer value
    int* q = static_cast<int*>(std::malloc(sizeof(int)));  // may reuse the same address
    *q = 2;
    if (p == q) {                                          // the comparison itself is not reliable
        *p = 3;                                            // "same address, so it must alias q"
        std::printf("same address: *q=%d\n", *q);
    } else {
        std::puts("different");
    }
    std::free(q);
}
