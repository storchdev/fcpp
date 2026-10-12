// std: c++17
#include <cstdio>
#include <typeinfo>

struct Base {
    virtual ~Base() = default;
    void report() const { std::printf("typeid after construction: %s\n", typeid(*this).name()); }
};
struct Derived : Base {};

int main() {
    Derived d;
    d.report();                                // ask after the object is complete
}
