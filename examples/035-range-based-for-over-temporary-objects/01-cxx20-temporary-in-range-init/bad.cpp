// std: c++20
// sanitize: address
// Before C++23, the temporary Box in make().items() is destroyed before the loop body runs.
#include <cstdio>
#include <string>
#include <vector>

struct Box {
    std::vector<std::string> v{"a-long-enough-string-to-defeat-sso-0123456789", "b-long-enough-string-to-defeat-sso-0123456789"};
    const std::vector<std::string>& items() const { return v; }   // reference into the Box
};

Box make() { return Box{}; }

int main() {
    for (const auto& s : make().items())   // C++20: Box dies after __range is initialized
        std::printf("%s\n", s.c_str());     // UB
}
