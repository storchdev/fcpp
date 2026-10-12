// std: c++17
// Begin the object's lifetime with placement new, use the pointer it returns, and destroy it explicitly.
#include <cstdio>
#include <new>

struct Widget {
    int id = 7;
    virtual int get() const { return id; }
    virtual ~Widget() = default;
};

int main() {
    alignas(Widget) unsigned char storage[sizeof(Widget)];
    Widget* w = new (storage) Widget;
    std::printf("%d\n", w->get());
    w->~Widget();
}
