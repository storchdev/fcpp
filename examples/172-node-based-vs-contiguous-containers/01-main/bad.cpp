// std: c++17
// Summing a std::list chases one pointer per element; a std::vector walks contiguous memory.
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <list>
#include <numeric>
#include <random>
#include <vector>

int main() {
    const int n = 2000000;
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::shuffle(order.begin(), order.end(), std::mt19937(1));
    std::list<int> list;
    for (int v : order) list.push_back(v);          // nodes allocated in a scattered order relative to their values
    long sum = 0;
    auto start = std::chrono::steady_clock::now();
    for (int r = 0; r < 20; ++r) for (int v : list) sum += v;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("std::list: sum = %ld, %lld ms\n", sum, (long long)ms);
}
