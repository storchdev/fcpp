// std: c++17
// A pure virtual function called (indirectly) from a constructor or destructor has no final overrider yet: UB.
#include <cstdio>

struct Base {
    Base() { init(); }                         // init() looks harmless
    virtual ~Base() = default;
    virtual void run() = 0;
    void init() { std::puts("init"); run(); }  // dispatches to Base::run, which is pure
};
struct Derived : Base {
    void run() override { std::puts("Derived::run"); }
};

int main() {
    Derived d;                                 // aborts with "pure virtual method called" in practice
    d.run();
}
