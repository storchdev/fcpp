// std: c++20
// Create the span after the last operation that can reallocate (or re-create it afterwards).
#include <cstdio>
#include <span>
#include <vector>

int main() {
    std::vector<int> v(4, 7);
    v.resize(1000);
    std::span<int> view(v);
    std::printf("%d\n", view[0]);
}
