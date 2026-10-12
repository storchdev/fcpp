// std: c++17
#include <cstdio>
#include <string>
#include <variant>

struct Thrower {
    Thrower() = default;
    Thrower(const Thrower&) { throw 1; }
    Thrower& operator=(const Thrower&) = default;
};

int main() {
    std::variant<std::string, Thrower> v = std::string("hello");
    Thrower t;
    try { v = t; } catch (int) {}
    if (v.valueless_by_exception()) v = std::string("recovered");   // check, then give it a value
    std::printf("valueless = %d, index = %zu\n", (int)v.valueless_by_exception(), v.index());
}
