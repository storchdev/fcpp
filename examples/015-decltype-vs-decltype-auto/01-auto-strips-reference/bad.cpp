// std: c++17
// A forwarding accessor declared `auto` returns a copy, so writes through it are lost.
#include <cstdio>
#include <vector>

struct Cell { int n = 0; void bump() { ++n; } };

template <class C>
auto at(C& c, std::size_t i) { return c[i]; }  // `auto` decays: returns Cell by value

int main() {
    std::vector<Cell> cells(2);
    at(cells, 0).bump();                       // bumps a temporary copy
    std::printf("cells[0].n = %d\n", cells[0].n);  // 0: the bump hit a temporary
}
