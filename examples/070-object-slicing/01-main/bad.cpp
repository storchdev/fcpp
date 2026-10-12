// std: c++17
// Copying a Derived into a Base by value keeps only the Base subobject: the derived part and the vptr's target are gone.
#include <cstdio>
#include <vector>

struct Shape {
    virtual ~Shape() = default;
    virtual const char* name() const { return "Shape"; }
};
struct Circle : Shape {
    double radius = 2.0;
    const char* name() const override { return "Circle"; }
};

void describe(Shape s) { std::printf("by value: %s\n", s.name()); }     // slices

int main() {
    Circle c;
    describe(c);                               // prints Shape

    std::vector<Shape> shapes;
    shapes.push_back(c);                       // also slices
    std::printf("in vector: %s\n", shapes[0].name());
}
