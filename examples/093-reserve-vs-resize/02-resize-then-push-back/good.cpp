// std: c++17
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v;
    v.reserve(3);                                  // capacity only: size stays 0
    for (int i = 1; i <= 3; ++i) v.push_back(i);
    std::printf("size = %zu:", v.size());
    for (int x : v) std::printf(" %d", x);
    std::printf("\n");
}
