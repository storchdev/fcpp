// std: c++17
#include <cstdio>
#include <string>

int main(int argc, char**) {
    std::string s = "original";
    std::string fallback = "fallback";         // same type on both arms: the result is an lvalue of that type
    bool pick = argc > 0;
    const std::string& r = pick ? s : fallback;
    s = "changed";
    std::printf("r = %s, s = %s\n", r.c_str(), s.c_str());   // r aliases s
}
