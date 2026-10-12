// std: c++17
// sanitize: memory
// Default-initialized locals of fundamental type are indeterminate; reading them is UB.
#include <cstdio>
#include <memory>

struct Point {
    int x;
    int y;
};

int main() {
    Point p;                          // default-initialization: x and y are indeterminate
    Point q{};                        // value-initialization: x and y are zero (looks almost identical!)
    auto buf = std::unique_ptr<int[]>(new int[4]);  // default-init: four indeterminate ints

    std::printf("q  = (%d, %d)\n", q.x, q.y);       // fine
    std::printf("p  = (%d, %d)\n", p.x, p.y);       // UB: reads indeterminate values
    std::printf("buf[0] = %d\n", buf[0]);            // UB: same, hidden behind new[]
}
