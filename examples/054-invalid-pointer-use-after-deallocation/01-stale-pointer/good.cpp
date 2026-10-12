// std: c++17
// One owner (a value or unique_ptr in the container); everything else uses indices or non-owning access under that owner.
#include <cstdio>
#include <memory>
#include <vector>

struct Session { int id; };

int main() {
    std::vector<std::unique_ptr<Session>> active;
    active.push_back(std::make_unique<Session>(Session{7}));
    for (const auto& x : active)
        std::printf("session %d\n", x->id);
    active.clear();                               // destroys the Session; no alias outlives it
}
