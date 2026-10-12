// std: c++20
// Prefer an owning member; if a reference member is intended, initialize it from a named object.
#include <cstdio>
#include <string>

struct Name { std::string text; };

int main() {
    Name braces{std::string("a-long-enough-string-to-defeat-sso-0123456789")};
    Name parens(std::string("a-long-enough-string-to-defeat-sso-0123456789"));
    std::printf("%s\n", braces.text.c_str());
    std::printf("%s\n", parens.text.c_str());
}
