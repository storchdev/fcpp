// std: c++17
// If constructing the new alternative throws, the variant is left valueless and visiting it throws.
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
    try { v = t; } catch (int) {}                  // the copy throws after the old string was destroyed
    std::printf("valueless = %d, index = %zu\n", (int)v.valueless_by_exception(), v.index());
    try {
        std::visit([](const auto&) {}, v);         // assumes exactly one active alternative
    } catch (const std::bad_variant_access& e) {
        std::printf("visit threw: %s\n", e.what());
    }
}
