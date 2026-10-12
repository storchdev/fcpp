// std: c++20
#include <algorithm>
#include <cstdio>
#include <vector>

std::vector<int> make() { return {1, 2, 3}; }

int main() {
    auto v = make();                                // keep the range alive while using its iterators
    auto it = std::ranges::find(v, 2);
    std::printf("%d\n", *it);
}
