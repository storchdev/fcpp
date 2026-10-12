// std: c++17
// Use copy construction/assignment (or std::copy for ranges); they know how to duplicate ownership.
#include <cstdio>
#include <string>
#include <type_traits>

int main() {
    static_assert(!std::is_trivially_copyable_v<std::string>);
    std::string a("a-long-enough-string-to-defeat-sso-0123456789");
    std::string b = a;
    std::printf("%s\n", b.c_str());
}
