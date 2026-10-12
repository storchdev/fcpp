// std: c++17
// A virtual call in a base constructor does not reach the derived override: the derived part does not exist yet.
#include <cstdio>

struct Shape {
    Shape() { describe(); }                          // intended: dispatch to the most derived class
    virtual ~Shape() = default;
    virtual void describe() const { std::puts("Shape::describe"); }
};

struct Circle : Shape {
    void describe() const override { std::puts("Circle::describe"); }
};

int main() {
    Circle c;        // prints "Shape::describe"
    c.describe();    // prints "Circle::describe"
}
