// std: c++20
// Name the owner so it outlives the loop (a C++20 init-statement keeps its scope tight).
#include <cstdio>
#include <string>
#include <vector>

struct Box {
    std::vector<std::string> v{"a-long-enough-string-to-defeat-sso-0123456789", "b-long-enough-string-to-defeat-sso-0123456789"};
    const std::vector<std::string>& items() const { return v; }
};

Box make() { return Box{}; }

int main() {
    for (const Box box = make(); const auto& s : box.items())
        std::printf("%s\n", s.c_str());
}
