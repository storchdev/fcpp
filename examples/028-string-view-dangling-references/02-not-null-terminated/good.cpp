// std: c++17
// Pass the length with %.*s (or use iostreams), or make a std::string when a terminator is required.
#include <cstdio>
#include <string>
#include <string_view>

int main() {
    const char buf[3] = {'a', 'b', 'c'};
    std::string_view sv(buf, 3);
    std::printf("%.*s\n", static_cast<int>(sv.size()), sv.data());
    std::string owned(sv);
    std::printf("%s\n", owned.c_str());
}
