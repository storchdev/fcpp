// std: c++17
// sanitize: address
// std::copy does not grow its destination: the output range must already exist.
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> src{1, 2, 3, 4};
    std::vector<int> dst(2);                       // room for two
    std::copy(src.begin(), src.end(), dst.begin());   // writes four
    std::printf("dst[0] = %d\n", dst[0]);
}
