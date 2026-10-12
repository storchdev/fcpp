// std: c++17
// `*opt` on an empty optional is undefined behavior; value() throws std::bad_optional_access instead.
#include <cstdio>
#include <optional>
#include <string>

std::optional<std::string> find_user(int id) {
    if (id == 1) return std::string("admin");
    return std::nullopt;
}

int main() {
    auto user = find_user(2);
    std::printf("user = %s\n", (*user).c_str());   // user is empty: UB
}
