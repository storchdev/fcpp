// std: c++17
#include <cstdio>
#include <string>

void put(bool) { std::printf("put(bool)\n"); }
void put(const std::string&) { std::printf("put(string)\n"); }

int main() {
    using namespace std::string_literals;
    put("hello"s);                                 // a std::string literal is an exact match
}
