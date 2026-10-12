// std: c++17
// Even without reallocation, insert shifts the elements after the insertion point: old iterators point at other elements.
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4};
    v.reserve(100);                                // no reallocation will happen
    auto it = std::find(v.begin(), v.end(), 3);
    v.insert(v.begin(), 0);                        // shifts everything right by one
    std::printf("*it = %d (expected 3)\n", *it);   // invalidated iterator: now designates the element 2
}
