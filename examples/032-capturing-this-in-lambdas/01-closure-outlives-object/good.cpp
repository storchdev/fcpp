// std: c++20
// Capture a copy of the object ([*this]) when the closure must outlive it.
#include <cstdio>
#include <functional>
#include <vector>

std::vector<std::function<void()>> callbacks;

struct Widget {
    int clicks = 41;
    void arm() { callbacks.push_back([*this] { std::printf("clicks=%d\n", clicks); }); }
};

int main() {
    auto* w = new Widget;
    w->arm();
    delete w;
    callbacks[0]();
}
