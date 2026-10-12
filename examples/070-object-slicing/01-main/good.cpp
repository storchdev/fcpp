// std: c++17
#include <cstdio>
#include <memory>
#include <vector>

struct Shape {
    Shape() = default;
    Shape(const Shape&) = delete;              // polymorphic base: make slicing a compile error
    Shape& operator=(const Shape&) = delete;
    virtual ~Shape() = default;
    virtual const char* name() const { return "Shape"; }
};
struct Circle : Shape {
    double radius = 2.0;
    const char* name() const override { return "Circle"; }
};

void describe(const Shape& s) { std::printf("by reference: %s\n", s.name()); }

int main() {
    Circle c;
    describe(c);

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    std::printf("in vector: %s\n", shapes[0]->name());
}
