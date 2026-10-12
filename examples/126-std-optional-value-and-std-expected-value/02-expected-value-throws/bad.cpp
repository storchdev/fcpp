// std: c++23
// expected::value() throws bad_expected_access on error: an "exception-free" function can still throw.
#include <cstdio>
#include <expected>
#include <string>

std::expected<int, std::string> parse(const std::string& s) {
    if (s.empty()) return std::unexpected("empty input");
    return std::stoi(s);
}

int main() {
    int n = parse("").value();                     // the error becomes an exception
    std::printf("n = %d\n", n);
}
