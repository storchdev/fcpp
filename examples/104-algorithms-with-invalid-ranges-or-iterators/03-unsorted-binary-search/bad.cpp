// std: c++17
// binary_search requires a range partitioned by the searched value; on unsorted data the answer is meaningless.
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{5, 1, 4, 2, 3};
    std::printf("binary_search(4) = %d\n", (int)std::binary_search(v.begin(), v.end(), 4));
    std::printf("binary_search(1) = %d (1 is in the vector)\n", (int)std::binary_search(v.begin(), v.end(), 1));
}
