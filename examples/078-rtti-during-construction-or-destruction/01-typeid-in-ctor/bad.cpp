// std: c++17
// During construction the dynamic type is the class being constructed: typeid and dynamic_cast see Base, not Derived.
#include <cstdio>
#include <typeinfo>

struct Derived;
struct Base {
    Base();
    virtual ~Base() = default;
};
struct Derived : Base {};

Base::Base() {
    std::printf("typeid in Base ctor: %s\n", typeid(*this).name());
    std::printf("dynamic_cast<Derived*>(this) in Base ctor: %p\n", static_cast<void*>(dynamic_cast<Derived*>(this)));
}

int main() {
    Derived d;
    std::printf("typeid after construction: %s\n", typeid(d).name());
}
