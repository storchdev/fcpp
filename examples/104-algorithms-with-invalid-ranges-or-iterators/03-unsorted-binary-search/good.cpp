// std: c++17
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{5, 1, 4, 2, 3};
    std::sort(v.begin(), v.end());
    std::printf("binary_search(4) = %d\n", (int)std::binary_search(v.begin(), v.end(), 4));
    std::printf("binary_search(1) = %d\n", (int)std::binary_search(v.begin(), v.end(), 1));
}
