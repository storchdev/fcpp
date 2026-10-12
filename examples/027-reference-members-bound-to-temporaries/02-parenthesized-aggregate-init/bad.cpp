// std: c++20
// sanitize: address
// Brace aggregate init extends a temporary bound to a reference member; C++20 parenthesized aggregate init does not.
#include <cstdio>
#include <string>

struct Name { const std::string& text; };

int main() {
    Name braces{std::string("a-long-enough-string-to-defeat-sso-0123456789")};     // extended: fine
    Name parens(std::string("a-long-enough-string-to-defeat-sso-0123456789"));     // C++20 parenthesized aggregate init: not extended
    std::printf("%s\n", braces.text.c_str());
    std::printf("%s\n", parens.text.c_str());   // UB
}
