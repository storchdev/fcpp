// std: c++20
// Constrain the forwarding constructor so it drops out when the argument is a Session.
#include <concepts>
#include <cstdio>
#include <type_traits>
#include <utility>

struct Options { int verbose = 0; };

class Session {
    static inline int next_id = 0;
    int id_;
public:
    template <class T>
        requires (!std::same_as<std::remove_cvref_t<T>, Session>)
    explicit Session(T&&) : id_(++next_id) {}
    Session(const Session&) = default;
    int id() const { return id_; }
};

int main() {
    Session a(Options{});
    Session b(a);
    const Session& r = a;
    Session d(r);
    std::printf("a=%d b=%d d=%d\n", a.id(), b.id(), d.id());
}
