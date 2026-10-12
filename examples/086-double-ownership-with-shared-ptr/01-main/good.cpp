// std: c++17
#include <memory>
#include <cstdio>

struct Widget { int id = 1; ~Widget() { std::puts("~Widget"); } };

int main() {
    auto a = std::make_shared<Widget>();       // never expose the raw pointer
    std::shared_ptr<Widget> b = a;             // copy the shared_ptr to share ownership
    std::printf("a.use_count=%ld b.use_count=%ld\n", a.use_count(), b.use_count());
}
