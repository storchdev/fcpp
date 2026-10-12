// std: c++17
#include <cstdio>
#include <string>

std::string make_greeting(const std::string& name) {
    return "hello, " + name;        // return by value; copy elision / move makes this cheap
}

std::string make_tag() { return "tag-42"; }

int main() {
    std::string g = make_greeting("world");
    std::printf("%s\n", g.c_str());
    std::printf("%s\n", make_tag().c_str());   // temporary lives until end of the full-expression
}
