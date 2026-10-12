// std: c++17
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> a{3, 1, 2};
    std::sort(a.begin(), a.end());
    std::printf("done\n");
}
