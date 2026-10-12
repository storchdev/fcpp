// std: c++17
// Let a container or smart pointer pick the matching form.
#include <cstdio>
#include <memory>
#include <vector>

int main() {
    auto values = std::make_unique<int[]>(4);
    values[3] = 4;
    std::vector<int> v{1, 2, 3, 4};
    std::printf("%d %d\n", values[3], v[3]);
}
