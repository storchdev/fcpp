// std: c++17
// When the arms differ in type, ?: yields a prvalue copy, not an alias of the chosen object.
#include <cstdio>
#include <string>

int main(int argc, char**) {
    std::string s = "original";
    bool pick = argc > 0;
    const std::string& r = pick ? s : "fallback";   // "fallback" converts to std::string, so s is copied too
    s = "changed";
    std::printf("r = %s, s = %s\n", r.c_str(), s.c_str());   // r is still "original"
}
