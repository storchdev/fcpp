// std: c++17
// Call describe() after construction, e.g. from a factory, instead of from the base constructor.
#include <cstdio>
#include <memory>

struct Shape {
    virtual ~Shape() = default;
    virtual void describe() const { std::puts("Shape::describe"); }
};

struct Circle : Shape {
    void describe() const override { std::puts("Circle::describe"); }
};

template <class T>
std::unique_ptr<T> create() {
    auto p = std::make_unique<T>();
    p->describe();                 // the object is fully constructed here
    return p;
}

int main() {
    auto c = create<Circle>();     // prints "Circle::describe"
}
