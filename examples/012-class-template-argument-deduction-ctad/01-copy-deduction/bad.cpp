// std: c++17
// With one braced argument of the class's own type, CTAD prefers the copy deduction candidate.
#include <cstdio>
#include <type_traits>
#include <vector>

int main() {
    std::vector<int> row{1, 2, 3};

    std::vector grid{row};            // vector<int> (a copy of row), NOT vector<vector<int>>
    std::vector grid2{row, row};      // vector<vector<int>>: two elements

    static_assert(std::is_same_v<decltype(grid), std::vector<int>>);
    static_assert(std::is_same_v<decltype(grid2), std::vector<std::vector<int>>>);

    std::printf("grid.size=%zu grid2.size=%zu\n", grid.size(), grid2.size());   // 3 and 2
}
