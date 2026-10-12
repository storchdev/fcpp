// std: c++17
// sanitize: address
// malloc/free and new/delete are separate families; mixing them is undefined.
#include <cstdio>
#include <cstdlib>

struct Point { int x, y; };

int main() {
    Point* p = static_cast<Point*>(std::malloc(sizeof(Point)));
    p->x = 1;
    p->y = 2;
    std::printf("%d %d\n", p->x, p->y);
    delete p;                               // UB: memory came from malloc
}
