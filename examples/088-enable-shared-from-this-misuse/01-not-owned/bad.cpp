// std: c++17
// shared_from_this() needs an existing shared_ptr that owns the object; otherwise it throws std::bad_weak_ptr.
#include <cstdio>
#include <memory>

struct Session : std::enable_shared_from_this<Session> {
    std::shared_ptr<Session> self() { return shared_from_this(); }
};

int main() {
    Session s;                                 // automatic object: no shared_ptr owns it
    auto p = s.self();                         // throws std::bad_weak_ptr
    std::printf("use_count=%ld\n", p.use_count());
}
