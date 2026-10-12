// std: c++17
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    int folded = std::accumulate(v.begin(), v.end(), 100, [](int a, int b) { return a - b; });   // defined left-to-right order
    int reduced = std::reduce(v.begin(), v.end(), 100);   // std::plus is associative and commutative
    std::printf("accumulate(minus) = %d, reduce(plus) = %d\n", folded, reduced);
}
