// std: c++17
// sanitize: address
// The temporary string returned by a function dies at the end of the full-expression; the pointer outlives it.
#include <cstdio>
#include <string>

std::string config_path() { return std::string("/etc/a-long-enough-path-to-defeat-sso/app.conf"); }

int main() {
    const char* p = config_path().c_str();   // temporary destroyed at the ';'
    std::printf("%s\n", p);                  // UB: heap-use-after-free
}
