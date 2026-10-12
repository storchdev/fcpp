// std: c++20
#include <cstdio>
#include <utility>
#include <vector>

int main() {
    int a = -1;
    unsigned b = 1;
    std::printf("-1 < 1u is %s\n", std::cmp_less(a, b) ? "true" : "false");   // true: compares values

    std::vector<int> v{1, 2, 3};
    int idx = -1;
    if (idx >= 0 && static_cast<std::size_t>(idx) < v.size())                   // explicit range check
        std::printf("idx %d is in range\n", idx);
    else
        std::printf("idx %d is out of range\n", idx);
}
