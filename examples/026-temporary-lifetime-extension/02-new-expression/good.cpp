// std: c++20
// Own the data: a std::string member keeps its own copy, so the object can live on the heap safely.
#include <cstdio>
#include <memory>
#include <string>

struct Label { std::string text; };

int main() {
    auto heap = std::make_unique<Label>(Label{std::string("a-long-enough-string-to-defeat-sso-0123456789")});
    std::printf("%s\n", heap->text.c_str());
}
