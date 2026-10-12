// std: c++17
// Inside a constructor or destructor the dynamic type is the class being constructed, not the most-derived one.
#include <cstdio>

struct Base {
    Base() { std::printf("Base ctor: %s\n", name()); }       // calls Base::name, not Derived::name
    virtual ~Base() { std::printf("Base dtor: %s\n", name()); }
    virtual const char* name() const { return "Base"; }
};
struct Derived : Base {
    const char* name() const override { return "Derived"; }
};

int main() {
    Derived d;
    std::printf("main: %s\n", d.name());
}
