// std: c++17
// With an explicit constructor, name the type (direct-initialization still works).
#include <cstdio>

struct Point {
    explicit Point(int x, int y) : x(x), y(y) {}
    int x, y;
};

Point origin() {
    return Point{0, 0};
}

int main() {
    Point p = origin();
    Point q(1, 2);
    Point r{3, 4};
    std::printf("%d %d %d %d %d %d\n", p.x, p.y, q.x, q.y, r.x, r.y);
}
