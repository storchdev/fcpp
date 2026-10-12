// std: c++17
// sanitize: address
// `decltype(auto)` + `return (x);` deduces `int&` to a local: a dangling reference.
#include <cstdio>

decltype(auto) next_id() {
    int id = 41;
    ++id;
    return (id);   // (id) is an lvalue expression -> decltype((id)) is int&
}

int main() {
    int v = next_id();  // reads through a dangling reference
    std::printf("%d\n", v);
}
