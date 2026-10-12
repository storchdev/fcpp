// std: c++17
#include <climits>
#include <cstdio>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v{INT_MAX, 1};
    auto sum = std::accumulate(v.begin(), v.end(), 0LL);   // T = long long
    std::printf("sum = %lld\n", sum);
}
