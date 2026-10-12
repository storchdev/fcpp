// std: c++17
#include <cstdio>
#include <string>
#include <variant>

int main() {
    std::variant<int, std::string> v = 42;
    if (auto* s = std::get_if<std::string>(&v)) std::printf("%s\n", s->c_str());   // nullptr when it holds something else
    else std::printf("not a string, index = %zu\n", v.index());
}
