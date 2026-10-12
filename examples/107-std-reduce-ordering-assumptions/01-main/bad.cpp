// std: c++17
// reduce may group and reorder operands arbitrarily, so a non-associative operation gives a different answer than accumulate.
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    auto minus = [](int a, int b) { return a - b; };
    int reduced = std::reduce(v.begin(), v.end(), 100, minus);
    int folded = std::accumulate(v.begin(), v.end(), 100, minus);
    std::printf("reduce = %d, accumulate = %d\n", reduced, folded);
}
