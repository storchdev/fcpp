// std: c++17
// any_cast<T> only succeeds for the exact stored type: a string literal is stored as const char*, not std::string.
#include <any>
#include <cstdio>
#include <string>

int main() {
    std::any a = "hello";                           // stores const char*
    try {
        std::string s = std::any_cast<std::string>(a);
        std::printf("%s\n", s.c_str());
    } catch (const std::bad_any_cast& e) {
        std::printf("bad_any_cast: %s\n", e.what());
    }
}
