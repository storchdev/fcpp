// std: c++17
#include <cstdio>

struct Base {
    void f(int) { std::puts("Base::f(int)"); }
};
struct Derived : Base {
    using Base::f;
    void f(double) { std::puts("Derived::f(double)"); }
};

int main() {
    Derived d;
    d.f(1);                                    // Base::f(int): the better match
    d.f(1.5);
}
