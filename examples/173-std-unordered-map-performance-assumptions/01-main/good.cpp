// std: c++17
#include <chrono>
#include <cstdio>
#include <unordered_map>

int main() {
    std::unordered_map<int, int> m;
    m.reserve(20000);
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 20000; ++i) m[i] = i;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
    std::printf("default hash: size = %zu, %lld ms\n", m.size(), (long long)ms);
}
