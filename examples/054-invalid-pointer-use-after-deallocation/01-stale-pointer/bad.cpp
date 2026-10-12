// std: c++17
// sanitize: address
// A second pointer to a deleted object still holds the old address, which is now invalid.
#include <cstdio>
#include <vector>

struct Session { int id; };

int main() {
    std::vector<Session*> active;
    Session* s = new Session{7};
    active.push_back(s);
    delete s;                                    // s is dangling; so is active[0]
    for (Session* x : active)
        std::printf("session %d\n", x->id);      // UB: use after free
}
