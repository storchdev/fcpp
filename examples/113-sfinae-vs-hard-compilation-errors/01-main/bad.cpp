// expect: compile-error
// std: c++17
// Only substitution into the declaration is SFINAE; an error inside a deduced-return function body is a hard error.
#include <cstdio>

template <class T>
auto describe(const T& t) { return t.size(); }     // body is instantiated to deduce the return type

int describe(...) { return -1; }                   // intended fallback for types without size()

int main() {
    std::printf("%d\n", (int)describe(5));         // error: request for member 'size' in an int
}
