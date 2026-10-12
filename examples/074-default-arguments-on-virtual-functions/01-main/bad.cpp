// std: c++17
// Default arguments are bound statically to the type of the expression; the function body is chosen dynamically.
#include <cstdio>

struct Base {
    virtual ~Base() = default;
    virtual void greet(int times = 1) const { std::printf("Base::greet(%d)\n", times); }
};
struct Derived : Base {
    void greet(int times = 5) const override { std::printf("Derived::greet(%d)\n", times); }
};

int main() {
    Derived d;
    const Base& b = d;
    b.greet();                                 // Derived::greet with Base's default: 1
    d.greet();                                 // Derived::greet with Derived's default: 5
}
