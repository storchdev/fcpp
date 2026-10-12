// std: c++17
// sanitize: address
// Deleting a Derived through a Base* whose destructor is not virtual is UB.
#include <cstdio>
#include <string>

struct Base {
    virtual void f() {}                        // polymorphic, so people will delete through Base*
    ~Base() { std::puts("~Base"); }            // but the destructor is not virtual
};
struct Derived : Base {
    std::string payload = std::string(100, 'x');   // heap allocation owned by the Derived part
    ~Derived() { std::puts("~Derived"); }
};

int main() {
    Base* p = new Derived;
    delete p;                                  // only ~Base runs; payload leaks; sized delete uses the wrong size
}
