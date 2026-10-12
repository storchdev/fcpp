// std: c++17
// Destroy the old object, then construct the new one. (Plain assignment is simpler still.)
#include <cstdio>
#include <new>
#include <string>

int main() {
    std::string s("a-long-enough-string-to-defeat-sso-0123456789");
    s.~basic_string();
    new (&s) std::string("another-long-enough-string-to-defeat-sso-012345");
    std::printf("%s\n", s.c_str());
}
