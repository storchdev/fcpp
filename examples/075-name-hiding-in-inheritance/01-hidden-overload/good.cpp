// std: c++17
#include <string>

struct Base {
    void set(int) {}
    void set(const std::string&) {}
};
struct Derived : Base {
    using Base::set;                           // bring the hidden overloads back into scope
    void set(double) {}
};

int main() {
    Derived d;
    d.set("x");
}
