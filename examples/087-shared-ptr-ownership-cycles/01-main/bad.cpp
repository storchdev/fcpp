// std: c++17
// sanitize: address
// Two nodes owning each other through shared_ptr never reach a zero count: neither destructor runs.
#include <memory>
#include <cstdio>

struct Node {
    std::shared_ptr<Node> other;
    ~Node() { std::puts("~Node"); }
};

__attribute__((noinline)) void build() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->other = b;
    b->other = a;                              // cycle: both counts stay at 1 after a and b go out of scope
    std::printf("a.use_count=%ld b.use_count=%ld\n", a.use_count(), b.use_count());
}

int main() {
    build();
    std::puts("build() returned; no ~Node was printed");
}
