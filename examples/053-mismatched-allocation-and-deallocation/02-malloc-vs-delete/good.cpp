// std: c++17
// Use one family per allocation: here the owner is a unique_ptr that calls delete.
#include <cstdio>
#include <memory>

struct Point { int x, y; };

int main() {
    auto p = std::make_unique<Point>(Point{1, 2});
    std::printf("%d %d\n", p->x, p->y);
}
