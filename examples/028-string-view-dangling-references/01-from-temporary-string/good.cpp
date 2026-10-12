// std: c++17
// Keep the owner alive in a named variable (or return std::string if the caller needs ownership).
#include <cstdio>
#include <string>
#include <string_view>

std::string_view trim_prefix(std::string_view s) { return s.substr(s.find(':') + 1); }
std::string read_line() { return std::string("key:a-long-enough-value-to-defeat-sso-0123456789"); }

int main() {
    const std::string line = read_line();                 // owner outlives the view
    std::string_view value = trim_prefix(line);
    std::printf("%c... (%zu chars)\n", value[0], value.size());
}
