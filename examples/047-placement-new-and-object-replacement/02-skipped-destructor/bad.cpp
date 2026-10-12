// std: c++17
// sanitize: address
// Constructing a new object over a live std::string without destroying it first leaks the old heap buffer.
#include <cstdio>
#include <new>
#include <string>

int main() {
    std::string s("a-long-enough-string-to-defeat-sso-0123456789");
    new (&s) std::string("another-long-enough-string-to-defeat-sso-012345");   // old buffer is never freed
    std::printf("%s\n", s.c_str());
}
