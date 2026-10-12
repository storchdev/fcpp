// std: c++17
#include <cstdio>
#include <memory>

struct Session : std::enable_shared_from_this<Session> {
    std::shared_ptr<Session> self() { return shared_from_this(); }
};

int main() {
    auto s = std::make_shared<Session>();      // owned by a shared_ptr from the start
    auto p = s->self();
    std::printf("use_count=%ld\n", p.use_count());
}
