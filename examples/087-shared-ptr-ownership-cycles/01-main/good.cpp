// std: c++17
#include <memory>
#include <cstdio>

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;                  // the back-link does not own
    ~Node() { std::puts("~Node"); }
};

__attribute__((noinline)) void build() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->prev = a;
    std::printf("a.use_count=%ld b.use_count=%ld\n", a.use_count(), b.use_count());
}

int main() {
    build();
    std::puts("build() returned");
}
