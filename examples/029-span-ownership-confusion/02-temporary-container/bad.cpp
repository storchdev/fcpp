// std: c++20
// sanitize: address
// span<const T> accepts an rvalue container; the container dies at the end of the statement.
#include <cstdio>
#include <span>
#include <vector>

std::vector<int> make() { return std::vector<int>(1000, 7); }

int main() {
    std::span<const int> view = make();    // compiles because the element type is const
    std::printf("%d\n", view[0]);          // UB: heap-use-after-free
}
