// std: c++17
// Name the string, or consume the pointer within the same full-expression.
#include <cstdio>
#include <string>

std::string config_path() { return std::string("/etc/a-long-enough-path-to-defeat-sso/app.conf"); }

int main() {
    const std::string path = config_path();
    std::printf("%s\n", path.c_str());
    std::printf("%s\n", config_path().c_str());   // fine: the temporary lives until the end of this statement
}
