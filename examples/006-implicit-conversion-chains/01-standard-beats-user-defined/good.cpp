// std: c++20
// Constrain the bool overload so only an actual bool can reach it.
#include <concepts>
#include <cstdio>
#include <string>

void log(const std::string& msg) { std::printf("string: %s\n", msg.c_str()); }

template <std::same_as<bool> B>
void log(B flag) { std::printf("bool: %d\n", flag); }

int main() {
    log("disk full");   // const char[10] -> std::string; the template is not viable
    log(true);
}
