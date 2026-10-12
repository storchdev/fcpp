// std: c++20
// Keep the owner in a named variable for as long as the span is used.
#include <cstdio>
#include <span>
#include <vector>

std::vector<int> make() { return std::vector<int>(1000, 7); }

int main() {
    const std::vector<int> owner = make();
    std::span<const int> view = owner;
    std::printf("%d\n", view[0]);
}
