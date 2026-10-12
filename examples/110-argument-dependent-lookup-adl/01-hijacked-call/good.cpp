// std: c++17
#include <cstdio>

namespace lib {
struct Widget { operator int() const { return 7; } };
void show(const Widget&) { std::printf("lib::show(Widget)\n"); }
}

void show(int) { std::printf("::show(int)\n"); }

int main() {
    lib::Widget w;
    ::show(w);                                     // qualified name: no ADL
}
