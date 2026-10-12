// std: c++17
// A pointer-to-bool conversion is a standard conversion, which outranks the user-defined conversion to std::string.
#include <cstdio>
#include <string>

void put(bool) { std::printf("put(bool)\n"); }
void put(const std::string&) { std::printf("put(string)\n"); }

int main() {
    put("hello");                                  // picks bool
}
