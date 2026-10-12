// std: c++17
// sanitize: undefined
// reinterpret_cast gives a pointer value; no Widget exists in the buffer, so calling a member on it is UB.
#include <cstdio>

struct Widget {
    int id = 7;
    virtual int get() const { return id; }
    virtual ~Widget() = default;
};

int main() {
    alignas(Widget) unsigned char storage[sizeof(Widget)] = {};
    auto* w = reinterpret_cast<Widget*>(storage);   // no constructor ran; no object, no vptr
    std::printf("%d\n", w->get());                    // UB
}
