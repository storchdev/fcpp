// std: c++17
// "Average O(1)" assumes a decent hash: with many keys in the same bucket every operation is a linear scan.
#include <chrono>
#include <cstdio>
#include <unordered_map>

struct BadHash { std::size_t operator()(int) const { return 42; } };   // every key collides

int main() {
    std::unordered_map<int, int, BadHash> m;
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 20000; ++i) m[i] = i;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("constant hash: size = %zu, %lld ms\n", m.size(), (long long)ms);
}
