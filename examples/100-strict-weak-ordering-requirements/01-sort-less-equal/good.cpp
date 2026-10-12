// std: c++17
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v(100, 5);
    std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });    // strict: equal elements are not "less"
    std::printf("sorted %zu elements\n", v.size());
}
