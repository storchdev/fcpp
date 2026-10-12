// std: c++17
#include <cstdio>
#include <memory>
#include <string>

struct Resource {
    std::string name = std::string(40, 'r');
    ~Resource() { std::puts("~Resource"); }
};

__attribute__((noinline)) void use() {
    auto p = std::make_unique<Resource>();
    p.reset();                                 // destroys the object now
}

int main() {
    use();
    std::puts("use() returned");
}
