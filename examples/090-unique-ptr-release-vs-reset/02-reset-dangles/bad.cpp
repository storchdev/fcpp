// std: c++17
// sanitize: address
// reset() destroys the object, so a raw pointer taken earlier with get() dangles (release() would have kept it alive).
#include <cstdio>
#include <memory>

struct Config { int level = 3; };

int main() {
    auto p = std::make_unique<Config>();
    Config* raw = p.get();
    p.reset();                                 // deletes the Config
    std::printf("level = %d\n", raw->level);   // use after free
}
