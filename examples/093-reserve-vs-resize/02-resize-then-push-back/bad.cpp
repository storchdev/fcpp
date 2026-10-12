// std: c++17
// resize() creates elements: push_back after resize(n) appends after n zeros instead of filling the vector.
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v;
    v.resize(3);                                   // meant as "make room for 3"
    for (int i = 1; i <= 3; ++i) v.push_back(i);
    std::printf("size = %zu:", v.size());
    for (int x : v) std::printf(" %d", x);
    std::printf("\n");
}
