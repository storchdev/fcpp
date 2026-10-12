// std: c++17
// Only give a class an initializer_list constructor if it really is a "list of elements" type,
// and use parentheses when you mean "call this constructor".
#include <cstdio>
#include <initializer_list>

struct Widget {                       // no initializer_list constructor: braces and parentheses agree
    Widget(int, bool) { std::puts("Widget(int, bool)"); }
    Widget(int, double) { std::puts("Widget(int, double)"); }
};

struct Bag {                          // a real container: {} is the elements
    Bag(std::initializer_list<int> il) { std::printf("Bag with %zu elements\n", il.size()); }
};

int main() {
    Widget w1{10, true};
    Widget w2{10, 5.0};
    Bag b{10, 20, 30};
    (void)w1; (void)w2; (void)b;
}
