// std: c++17
// Two-phase initialization: construct first, then call init() when the derived part exists.
#include <cstdio>
#include <memory>

struct Base {
    virtual ~Base() = default;
    virtual void hook() = 0;
    void init() { hook(); }
};

struct Derived : Base {
    void hook() override { std::puts("Derived::hook"); }
};

int main() {
    auto d = std::make_unique<Derived>();
    d->init();
}
