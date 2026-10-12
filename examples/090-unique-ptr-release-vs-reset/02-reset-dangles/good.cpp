// std: c++17
#include <cstdio>
#include <memory>

struct Config { int level = 3; };

int main() {
    auto p = std::make_unique<Config>();
    Config* raw = p.release();                 // ownership transferred to us
    std::printf("level = %d\n", raw->level);
    delete raw;                                // now we must delete it ourselves
}
