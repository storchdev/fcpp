// std: c++17
// std::remove only moves the kept elements forward; the container keeps its size.
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 2};
    std::remove(v.begin(), v.end(), 2);            // returns the new logical end, which is ignored
    std::printf("size = %zu:", v.size());
    for (int x : v) std::printf(" %d", x);
    std::printf("\n");
}
