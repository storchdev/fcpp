// std: c++17
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <numeric>
#include <random>
#include <vector>

int main() {
    const int n = 2000000;
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::shuffle(order.begin(), order.end(), std::mt19937(1));
    std::vector<int> vec(order.begin(), order.end());
    long sum = 0;
    auto start = std::chrono::steady_clock::now();
    for (int r = 0; r < 20; ++r) for (int v : vec) sum += v;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("std::vector: sum = %ld, %lld ms\n", sum, (long long)ms);
}
