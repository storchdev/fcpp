// std: c++17
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v(5);                         // or v.resize(5): five value-initialized elements exist
    for (int i = 0; i < 5; ++i) v[i] = i * i;
    std::printf("size = %zu\n", v.size());
    for (int x : v) std::printf("%d ", x);
    std::printf("\n");
}
