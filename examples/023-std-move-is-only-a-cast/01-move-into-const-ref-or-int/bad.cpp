// std: c++17
// std::move only casts. Passing the result to `const T&` or to a trivially copyable type moves nothing.
#include <cstdio>
#include <string>
#include <utility>

void inspect(const std::string& s) { std::printf("inspect: %zu bytes\n", s.size()); }

int main() {
    std::string s = "0123456789012345678901234567890123456789";
    inspect(std::move(s));                        // binds to const&: no move
    std::printf("after inspect: %zu bytes\n", s.size());   // 40

    int n = 5;
    int m = std::move(n);                         // int has no move: this is a copy
    std::printf("n=%d m=%d\n", n, m);             // n=5 m=5
}
