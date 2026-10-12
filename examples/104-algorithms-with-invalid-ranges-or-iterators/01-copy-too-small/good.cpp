// std: c++17
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> src{1, 2, 3, 4};
    std::vector<int> dst;
    std::copy(src.begin(), src.end(), std::back_inserter(dst));   // appends as it goes
    std::printf("dst.size() = %zu\n", dst.size());
}
