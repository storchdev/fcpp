// std: c++17
#include <cstdio>
#include <optional>
#include <string>

std::optional<std::string> find_user(int id) {
    if (id == 1) return std::string("admin");
    return std::nullopt;
}

int main() {
    auto user = find_user(2);
    std::printf("user = %s\n", user ? user->c_str() : "(none)");   // check first (or use value() to get an exception)
}
