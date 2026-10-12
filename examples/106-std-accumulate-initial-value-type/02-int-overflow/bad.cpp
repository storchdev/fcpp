// std: c++17
// sanitize: undefined
// Summing int elements into an int accumulator overflows; the type of init, not of the elements, sets the width.
#include <climits>
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v{INT_MAX, 1};
    auto sum = std::accumulate(v.begin(), v.end(), 0);   // T = int
    std::printf("sum = %d\n", sum);
}
