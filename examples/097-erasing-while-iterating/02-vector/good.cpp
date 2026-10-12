// std: c++17
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{2, 4, 6, 1};
    v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());   // erase-remove (C++20: std::erase_if)
    std::printf("size = %zu:", v.size());
    for (int x : v) std::printf(" %d", x);
    std::printf("\n");
}
