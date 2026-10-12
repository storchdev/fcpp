// std: c++17
// reserve() changes capacity, not size: indexing past size() is undefined even inside the allocated storage.
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v;
    v.reserve(5);
    for (int i = 0; i < 5; ++i) v[i] = i * i;      // elements do not exist yet
    std::printf("size = %zu\n", v.size());
    for (int x : v) std::printf("%d ", x);         // prints nothing
    std::printf("\n");
}
