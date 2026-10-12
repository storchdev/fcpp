// std: c++17
// Calling a pure virtual function (indirectly) from a constructor is undefined behavior.
#include <cstdio>

struct Base {
    Base() { init(); }                 // the call to the pure virtual happens inside init()
    virtual ~Base() = default;
    virtual void hook() = 0;
    void init() { hook(); }
};

struct Derived : Base {
    void hook() override { std::puts("Derived::hook"); }
};

int main() {
    Derived d;                         // aborts: "pure virtual method called"
}
