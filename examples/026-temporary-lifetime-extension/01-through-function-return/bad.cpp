// std: c++17
// sanitize: address
// Lifetime extension applies only to the reference bound *directly* to the temporary, not through a function call.
#include <cstdio>
#include <string>

const std::string& pick(const std::string& s) { return s; }   // returns its argument: looks harmless

int main() {
    const std::string& direct = std::string("a-long-enough-string-to-defeat-sso-0123456789");           // extended: lives as long as 'direct'
    const std::string& via_call = pick(std::string("a-long-enough-string-to-defeat-sso-0123456789"));   // the temporary dies at the ';' -- via_call dangles
    std::printf("%s\n", direct.c_str());                      // ok
    std::printf("%s\n", via_call.c_str());                    // UB: use after the temporary's destruction
}
