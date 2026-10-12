// expect: compile-error
// std: c++17
// A friend defined only inside a class is found by ADL alone: the argument must be of that class.
// g++:     error: 'inspect' was not declared in this scope
// clang++: error: use of undeclared identifier 'inspect'
#include <cstdio>

struct Meter {
    Meter(int v = 0) : value(v) {}                 // implicit conversion from int
    int value;
    friend void inspect(const Meter& m) { std::printf("%d m\n", m.value); }
};

int main() {
    inspect(Meter{3});                             // fine: ADL
    inspect(3);                                    // error: int has no associated class, so the friend is invisible
}
