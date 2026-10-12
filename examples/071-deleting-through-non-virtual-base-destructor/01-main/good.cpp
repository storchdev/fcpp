// std: c++17
#include <cstdio>
#include <memory>
#include <string>

struct Base {
    virtual void f() {}
    virtual ~Base() { std::puts("~Base"); }    // virtual: deleting through Base* runs ~Derived first
};
struct Derived : Base {
    std::string payload = std::string(100, 'x');
    ~Derived() override { std::puts("~Derived"); }
};

int main() {
    std::unique_ptr<Base> p = std::make_unique<Derived>();
    // alternative for a Base that is never deleted polymorphically: a protected non-virtual destructor
}
