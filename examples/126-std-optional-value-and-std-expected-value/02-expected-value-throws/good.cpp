// std: c++23
#include <cstdio>
#include <expected>
#include <string>

std::expected<int, std::string> parse(const std::string& s) {
    if (s.empty()) return std::unexpected("empty input");
    return std::stoi(s);
}

int main() {
    auto r = parse("");
    if (!r) { std::printf("error: %s\n", r.error().c_str()); return 0; }   // handle the error value explicitly
    std::printf("n = %d\n", *r);
}
