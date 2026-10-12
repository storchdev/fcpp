// std: c++17
#include <cstdio>

template <class T> struct Box { T get() const { return v; } T v; };   // definition visible where it is used

int main() {
    Box<int> b{3};
    std::printf("%d\n", b.get());
}
