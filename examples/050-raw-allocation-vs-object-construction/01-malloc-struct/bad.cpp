// std: c++17
// sanitize: memory
// malloc returns storage, not an object: default member initializers never ran.
#include <cstdio>
#include <cstdlib>

struct Config {
    int retries = 3;          // only applied by a constructor
    bool verbose = true;
};

[[gnu::noinline]] Config* make_config() {
    return static_cast<Config*>(std::malloc(sizeof(Config)));   // no Config object exists here
}

int main() {
    Config* c = make_config();
    if (c->retries == 3)                  // UB: reads storage that holds no object
        std::puts("default retries");
    std::free(c);
}
