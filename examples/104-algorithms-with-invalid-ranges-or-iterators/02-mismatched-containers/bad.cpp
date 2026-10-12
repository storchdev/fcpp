// std: c++17
// sanitize: address
// first and last must belong to the same range: begin() of one container with end() of another is not a range.
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> a{3, 1, 2};
    std::vector<int> b{9, 8, 7, 6, 5, 4};
    std::sort(a.begin(), b.end());                 // typo: should be a.end()
    std::printf("done\n");
}
