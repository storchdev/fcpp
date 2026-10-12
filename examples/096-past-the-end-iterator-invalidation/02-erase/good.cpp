// std: c++17
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4};
    v.erase(v.begin());
    for (auto it = v.begin(); it != v.end(); ++it) std::printf("%d ", *it);   // ask for end() each time
    std::printf("\n");
}
