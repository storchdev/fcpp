// std: c++23
// sanitize: address
// In C++23 the range-for extends make(); a hand-written reference variable does not get that.
#include <cstdio>
#include <string>
#include <vector>

struct Box {
    std::vector<std::string> v{"a-long-enough-string-to-defeat-sso-0123456789", "b-long-enough-string-to-defeat-sso-0123456789"};
    const std::vector<std::string>& items() const { return v; }
};

Box make() { return Box{}; }

int main() {
    auto&& r = make().items();          // refactor: the Box is destroyed at this ';' even in C++23
    for (const auto& s : r)
        std::printf("%s\n", s.c_str());  // UB
}
