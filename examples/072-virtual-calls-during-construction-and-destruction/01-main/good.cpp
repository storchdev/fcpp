// std: c++17
#include <cstdio>
#include <memory>

struct Base {
    virtual ~Base() = default;
    virtual const char* name() const { return "Base"; }
    void init() { std::printf("init: %s\n", name()); }       // two-phase: call virtuals after construction
};
struct Derived : Base {
    const char* name() const override { return "Derived"; }
};

// A factory makes the second phase impossible to forget.
std::unique_ptr<Base> make() {
    auto p = std::make_unique<Derived>();
    p->init();
    return p;
}

int main() {
    auto p = make();
    std::printf("main: %s\n", p->name());
}
