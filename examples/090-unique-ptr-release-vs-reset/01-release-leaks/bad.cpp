// std: c++17
// sanitize: address
// release() gives up ownership without deleting; it is not a way to destroy the object.
#include <cstdio>
#include <memory>
#include <string>

struct Resource {
    std::string name = std::string(40, 'r');
    ~Resource() { std::puts("~Resource"); }
};

__attribute__((noinline)) void use() {
    auto p = std::make_unique<Resource>();
    p.release();                               // returns the pointer, which is dropped: leak
}

int main() {
    use();
    std::puts("use() returned; no ~Resource was printed");
}
