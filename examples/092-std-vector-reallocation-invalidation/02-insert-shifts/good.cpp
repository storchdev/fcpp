// std: c++17
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4};
    v.reserve(100);
    v.insert(v.begin(), 0);
    auto it = std::find(v.begin(), v.end(), 3);    // search after the modification (or use the iterator insert returns)
    std::printf("*it = %d\n", *it);
}
