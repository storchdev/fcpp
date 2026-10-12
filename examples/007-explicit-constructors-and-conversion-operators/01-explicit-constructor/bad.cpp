// std: c++17
// expect: compile-error
// `explicit` removes the constructor from copy-initialization and copy-list-initialization, including `return {...}`.
#include <cstdio>

struct Point {
    explicit Point(int x, int y) : x(x), y(y) {}
    int x, y;
};

Point origin() {
    return {0, 0};   // error: converting to 'Point' from initializer list would use explicit constructor
}

int main() {
    Point p = origin();
    std::printf("%d %d\n", p.x, p.y);
}
