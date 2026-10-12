// std: c++17
#include <cstdio>

struct Base {
    virtual ~Base() = default;
    virtual void run() = 0;
    void init() { std::puts("init"); run(); }  // called by the owner after construction
};
struct Derived : Base {
    void run() override { std::puts("Derived::run"); }
};

int main() {
    Derived d;
    d.init();
}
