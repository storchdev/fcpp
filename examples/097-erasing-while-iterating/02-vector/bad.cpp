// std: c++17
// erase(it) invalidates it: continuing with ++it skips the element that shifted into its place.
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{2, 4, 6, 1};
    for (auto it = v.begin(); it != v.end(); ++it)
        if (*it % 2 == 0) v.erase(it);             // it is invalid after this call
    std::printf("size = %zu:", v.size());
    for (int x : v) std::printf(" %d", x);
    std::printf("\n");
}
