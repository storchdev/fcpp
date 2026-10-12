// std: c++17
// Construct the object: `new Config` (or make_unique), or placement new / std::construct_at on raw storage.
#include <cstdio>
#include <memory>

struct Config {
    int retries = 3;
    bool verbose = true;
};

int main() {
    auto c = std::make_unique<Config>();
    if (c->retries == 3)
        std::puts("default retries");
}
