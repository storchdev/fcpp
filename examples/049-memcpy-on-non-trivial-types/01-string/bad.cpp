// std: c++17
// sanitize: address
// memcpy copies the bytes of a std::string, including its pointer to the heap buffer: two owners, one buffer.
#include <cstdio>
#include <cstring>
#include <string>

int main() {
    std::string a("a-long-enough-string-to-defeat-sso-0123456789");
    std::string b;
    std::memcpy(&b, &a, sizeof a);       // not a copy: b now shares a's buffer
    std::printf("%s\n", b.c_str());
}                                         // both destructors free the same buffer
