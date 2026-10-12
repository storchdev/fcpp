// std: c++17
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
    std::vector<double> v{0.5, 0.5, 0.5, 0.5};
    auto sum = std::accumulate(v.begin(), v.end(), 0.0);   // T = double
    std::printf("sum = %g\n", sum);
}
