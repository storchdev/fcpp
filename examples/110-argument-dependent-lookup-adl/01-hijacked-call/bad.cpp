// std: c++17
// An unqualified call also searches the namespaces of its argument types, and an exact match there beats a conversion here.
#include <cstdio>

namespace lib {
struct Widget { operator int() const { return 7; } };
void show(const Widget&) { std::printf("lib::show(Widget)\n"); }
}

void show(int) { std::printf("::show(int)\n"); }

int main() {
    lib::Widget w;
    show(w);                                       // intended ::show(int); ADL finds lib::show
}
