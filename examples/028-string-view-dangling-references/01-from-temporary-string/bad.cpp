// std: c++17
// sanitize: address
// std::string_view parameters accept temporaries; returning a view of the parameter dangles with the temporary.
#include <cstdio>
#include <string>
#include <string_view>

std::string_view trim_prefix(std::string_view s) { return s.substr(s.find(':') + 1); }
std::string read_line() { return std::string("key:a-long-enough-value-to-defeat-sso-0123456789"); }

int main() {
    std::string_view value = trim_prefix(read_line());   // std::string -> string_view implicit; temporary dies at ';'
    std::printf("%c... (%zu chars)\n", value[0], value.size());   // UB: heap-use-after-free
}
