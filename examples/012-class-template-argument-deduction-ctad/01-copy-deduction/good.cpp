// std: c++17
// When you mean "a container holding one row", say the element type.
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> row{1, 2, 3};

    std::vector<std::vector<int>> grid{row};       // one element, which is a row
    std::vector<std::vector<int>> grid2{row, row};

    std::printf("grid.size=%zu grid2.size=%zu\n", grid.size(), grid2.size());   // 1 and 2
}
