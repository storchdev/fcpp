// std: c++17
// operator* on an empty optional is undefined behavior; only value() checks.
#include <cstdio>
#include <optional>
#include <string>

int main() {
    std::optional<std::string> name;               // empty
    std::printf("length = %zu\n", (*name).size()); // no check: reads an object that does not exist
}
