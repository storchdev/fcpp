// std: c++17
// Hiding can also compile and silently pick the wrong function: d.f(1) calls f(double), not Base::f(int).
#include <cstdio>

struct Base {
    void f(int) { std::puts("Base::f(int)"); }
};
struct Derived : Base {
    void f(double) { std::puts("Derived::f(double)"); }
};

int main() {
    Derived d;
    d.f(1);                                    // Derived::f(double)
    static_cast<Base&>(d).f(1);                // Base::f(int)
}
