// std: c++17
#include <any>
#include <cstdio>
#include <string>

int main() {
    std::any a = std::string("hello");              // store the type you will ask for
    if (auto* s = std::any_cast<std::string>(&a)) std::printf("%s\n", s->c_str());   // pointer form returns nullptr instead of throwing
}
