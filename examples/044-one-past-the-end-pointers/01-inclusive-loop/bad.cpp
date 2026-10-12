// std: c++17
// sanitize: address
// a + 4 may be formed and compared, but not dereferenced; `<=` makes the loop dereference it.
#include <cstdio>

int main() {
    int a[4] = {1, 2, 3, 4};
    int sum = 0;
    for (int* p = a; p <= a + 4; ++p)   // should be `!=` (or `<`)
        sum += *p;                       // last iteration dereferences the one-past-the-end pointer
    std::printf("%d\n", sum);
}
