// std: c++17
// The accumulator has the type of the init argument: 0 is an int, so every partial sum is truncated.
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
    std::vector<double> v{0.5, 0.5, 0.5, 0.5};
    auto sum = std::accumulate(v.begin(), v.end(), 0);   // T = int
    std::printf("sum = %d (expected 2)\n", sum);
}
