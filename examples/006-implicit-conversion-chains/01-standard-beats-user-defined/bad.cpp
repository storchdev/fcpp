// std: c++17
// A string literal prefers the bool overload: pointer->bool is a standard conversion, ->std::string is user-defined.
#include <cstdio>
#include <string>

void log(const std::string& msg) { std::printf("string: %s\n", msg.c_str()); }
void log(bool flag) { std::printf("bool: %d\n", flag); }

int main() {
    log("disk full");               // calls log(bool)! prints "bool: 1"
    log(std::string("disk full"));  // calls log(const std::string&)
}
