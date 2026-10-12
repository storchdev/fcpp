// std: c++17
// expect: compile-error
// A name declared in Derived hides every Base member of that name, even with a different signature.
// g++ 16.2.1:     error: cannot convert 'const char [2]' to 'double'
// clang++ 23.1.1: error: cannot initialize a parameter of type 'double' with an lvalue of type 'const char[2]'
#include <string>

struct Base {
    void set(int) {}
    void set(const std::string&) {}
};
struct Derived : Base {
    void set(double) {}                        // hides both Base::set overloads
};

int main() {
    Derived d;
    d.set("x");                                // no conversion from const char* to double
}
