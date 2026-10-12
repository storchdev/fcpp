// std: c++23
// Either keep the whole expression in the range-for, or keep the owner in a named variable.
#include <cstdio>
#include <string>
#include <vector>

struct Box {
    std::vector<std::string> v{"a-long-enough-string-to-defeat-sso-0123456789", "b-long-enough-string-to-defeat-sso-0123456789"};
    const std::vector<std::string>& items() const { return v; }
};

Box make() { return Box{}; }

int main() {
    const Box box = make();
    auto&& r = box.items();
    for (const auto& s : r)
        std::printf("%s\n", s.c_str());
}
