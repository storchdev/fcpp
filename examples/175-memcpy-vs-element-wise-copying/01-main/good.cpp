// std: c++17
#include <algorithm>
#include <cstdio>
#include <string>
#include <type_traits>
#include <vector>

int main() {
    std::vector<std::string> src(3, std::string(80, 'x'));
    std::vector<std::string> dst(3);
    std::copy(src.begin(), src.end(), dst.begin()); // element-wise: copy-assigns each string
    std::vector<int> a{1, 2, 3}, b(3);
    std::copy(a.begin(), a.end(), b.begin());       // for trivially copyable types libraries may use memmove
    static_assert(!std::is_trivially_copyable_v<std::string>);
    static_assert(std::is_trivially_copyable_v<int>);
    std::printf("dst[0].size = %zu, b[2] = %d\n", dst[0].size(), b[2]);
}
