// std: c++17
// sanitize: address
// Returning a reference to a local: the object is destroyed when the function returns.
#include <cstdio>
#include <string>

const std::string& make_greeting(const std::string& name) {
    std::string s = "hello, " + name;
    return s;                       // dangling: s dies at the closing brace
}

const char* make_tag() {
    std::string t = "tag-42";
    return t.c_str();               // pointer into a destroyed string
}

int main() {
    const std::string& g = make_greeting("world");
    std::printf("%s\n", g.c_str());        // UB: use after scope
    std::printf("%s\n", make_tag());       // UB: dangling pointer
}
