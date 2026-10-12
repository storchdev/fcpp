// std: c++17
// Copy or move the result into an object (returning by value), or name the temporary so it outlives the use.
#include <cstdio>
#include <string>

std::string pick(const std::string& s) { return s; }   // by value: the result is itself a temporary that can be extended

int main() {
    const std::string& direct = std::string("a-long-enough-string-to-defeat-sso-0123456789");
    const std::string& via_call = pick(std::string("a-long-enough-string-to-defeat-sso-0123456789"));   // prvalue bound directly: extended
    std::printf("%s\n", direct.c_str());
    std::printf("%s\n", via_call.c_str());
}
