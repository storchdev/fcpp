// std: c++20
// Designated initializers (C++20) name the members, and the compiler checks the order.
#include <cstdio>

struct Window { int border; int height; int width; };

int main() {
    Window w{.border = 2, .height = 600, .width = 800};
    // Window bad{.width = 800, .border = 2};   // g++: error (order must match declaration); clang++: -Wreorder-init-list warning
    std::printf("w: %dx%d border=%d\n", w.width, w.height, w.border);
}
