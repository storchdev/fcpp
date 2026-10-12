// std: c++20
// sanitize: address
// `[=]` inside a member function captures `this` (a pointer); the closure then outlives the object.
#include <cstdio>
#include <functional>
#include <vector>

std::vector<std::function<void()>> callbacks;

struct Widget {
    int clicks = 41;
    void arm() { callbacks.push_back([=] { std::printf("clicks=%d\n", clicks); }); }   // reads this->clicks later
};

int main() {
    auto* w = new Widget;
    w->arm();
    delete w;               // the closure still holds the pointer
    callbacks[0]();         // UB: heap-use-after-free
}
