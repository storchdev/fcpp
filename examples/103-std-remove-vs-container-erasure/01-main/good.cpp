// std: c++17
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 2};
    v.erase(std::remove(v.begin(), v.end(), 2), v.end());   // erase-remove idiom (C++20: std::erase(v, 2))
    std::printf("size = %zu:", v.size());
    for (int x : v) std::printf(" %d", x);
    std::printf("\n");
}
