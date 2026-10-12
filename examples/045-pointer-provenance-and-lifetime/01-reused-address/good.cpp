// std: c++17
// Use the pointer that names the live object (q); never use p after free, and never compare it to prove identity.
#include <cstdio>
#include <cstdlib>

int main() {
    int* p = static_cast<int*>(std::malloc(sizeof(int)));
    *p = 1;
    std::free(p);
    p = nullptr;                                           // drop the stale value
    int* q = static_cast<int*>(std::malloc(sizeof(int)));
    *q = 2;
    *q = 3;
    std::printf("*q=%d\n", *q);
    std::free(q);
}
