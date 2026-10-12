// std: c++17
// An initializer_list constructor wins in list-initialization even when another constructor is an exact match.
#include <cstdio>
#include <initializer_list>

struct Widget {
    Widget() { std::puts("Widget()"); }
    Widget(int, bool) { std::puts("Widget(int, bool)"); }
    Widget(int, double) { std::puts("Widget(int, double)"); }
    Widget(std::initializer_list<long double>) { std::puts("Widget(initializer_list<long double>)"); }
};

int main() {
    Widget w1(10, true);   // Widget(int, bool)
    Widget w2{10, true};   // initializer_list<long double>: bool and int convert to long double
    Widget w3(10, 5.0);    // Widget(int, double)
    Widget w4{10, 5.0};    // initializer_list<long double> again
    Widget w5{};           // empty braces + default constructor: Widget(), not an empty list
    Widget w6{{}};         // now the initializer_list constructor is used, with one element
    (void)w1; (void)w2; (void)w3; (void)w4; (void)w5; (void)w6;
}
