// std: c++17
// `decltype(auto)` uses decltype rules on the return expression, so `c[i]` (an lvalue) yields `Cell&`.
#include <cstdio>
#include <type_traits>
#include <vector>

struct Cell { int n = 0; void bump() { ++n; } };

template <class C>
decltype(auto) at(C& c, std::size_t i) { return c[i]; }

int main() {
    std::vector<Cell> cells(2);
    static_assert(std::is_same_v<decltype(at(cells, 0)), Cell&>);
    at(cells, 0).bump();
    std::printf("cells[0].n = %d\n", cells[0].n);  // 1
}
