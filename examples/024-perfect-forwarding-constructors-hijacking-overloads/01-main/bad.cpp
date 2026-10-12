// std: c++17
// An unconstrained `T&&` constructor beats the copy constructor for non-const lvalues.
#include <cstdio>
#include <utility>

struct Options { int verbose = 0; };

class Session {
    static inline int next_id = 0;
    int id_;
public:
    template <class T>
    explicit Session(T&&) : id_(++next_id) {}   // "open a new session from any options object"
    Session(const Session&) = default;          // copy: same id
    int id() const { return id_; }
};

int main() {
    Session a(Options{});
    Session b(a);          // intended copy; T = Session&, an exact match, beats Session(const Session&)
    const Session& r = a;
    Session d(r);          // const lvalue: the copy constructor is the exact match here
    std::printf("a=%d b=%d d=%d\n", a.id(), b.id(), d.id());
}
