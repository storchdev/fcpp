// std: c++17
#include <cstdio>
#include <optional>
#include <string>

int main() {
    std::optional<std::string> name;
    std::printf("length = %zu\n", name.value_or("").size());   // or: if (name) ..., or value() inside a try
}
