// std: c++17
// Half-open ranges: iterate while p != end, or let a range-for do it.
#include <cstdio>

int main() {
    int a[4] = {1, 2, 3, 4};
    int sum = 0;
    for (int v : a) sum += v;
    for (const int* p = a; p != a + 4; ++p) sum += *p;
    std::printf("%d\n", sum);
}
