// std: c++17
// sanitize: address
// Two shared_ptrs built from the same raw pointer have two control blocks, so the object is deleted twice.
#include <memory>
#include <cstdio>

struct Widget { int id = 1; ~Widget() { std::puts("~Widget"); } };

int main() {
    Widget* raw = new Widget;
    std::shared_ptr<Widget> a(raw);
    std::shared_ptr<Widget> b(raw);            // independent control block: use_count of each is 1
    std::printf("a.use_count=%ld b.use_count=%ld\n", a.use_count(), b.use_count());
}
