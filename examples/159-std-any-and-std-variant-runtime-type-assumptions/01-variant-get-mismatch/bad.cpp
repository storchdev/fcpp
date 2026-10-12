// std: c++17
// std::get<T> on a variant holding a different alternative throws bad_variant_access; assuming the alternative is a runtime bet.
#include <cstdio>
#include <string>
#include <variant>

int main() {
    std::variant<int, std::string> v = 42;
    try {
        std::string s = std::get<std::string>(v);   // holds int: throws
        std::printf("%s\n", s.c_str());
    } catch (const std::bad_variant_access& e) {
        std::printf("bad_variant_access: %s\n", e.what());
    }
}
