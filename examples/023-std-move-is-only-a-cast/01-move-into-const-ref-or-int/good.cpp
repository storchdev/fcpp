// std: c++17
// Move into something that takes ownership (a by-value or && parameter); don't write std::move where no move happens.
#include <cstdio>
#include <string>
#include <utility>

void inspect(const std::string& s) { std::printf("inspect: %zu bytes\n", s.size()); }
void adopt(std::string s) { std::printf("adopt: %zu bytes\n", s.size()); }

int main() {
    std::string s = "0123456789012345678901234567890123456789";
    inspect(s);                                   // no std::move: nothing to give up
    adopt(std::move(s));                          // by-value parameter move-constructs from s
    std::printf("after adopt: %zu bytes\n", s.size());     // moved-from; libstdc++ leaves it empty

    int n = 5;
    int m = n;
    std::printf("n=%d m=%d\n", n, m);
}
