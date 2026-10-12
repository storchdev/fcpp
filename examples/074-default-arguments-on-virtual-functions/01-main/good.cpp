// std: c++17
#include <cstdio>

struct Base {
    virtual ~Base() = default;
    void greet(int times = 1) const { do_greet(times); }     // non-virtual interface: one default, in one place
private:
    virtual void do_greet(int times) const { std::printf("Base::greet(%d)\n", times); }
};
struct Derived : Base {
private:
    void do_greet(int times) const override { std::printf("Derived::greet(%d)\n", times); }
};

int main() {
    Derived d;
    const Base& b = d;
    b.greet();
    d.greet();
}
