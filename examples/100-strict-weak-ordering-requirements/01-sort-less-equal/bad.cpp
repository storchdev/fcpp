// std: c++17
// sanitize: address
// A comparator must be irreflexive: comp(x, x) == true violates strict weak ordering and std::sort may run off the range.
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v(100, 5);                    // many equal elements
    std::sort(v.begin(), v.end(), [](int a, int b) { return a <= b; });   // "ascending, allowing equal"
    std::printf("sorted %zu elements\n", v.size());
}
