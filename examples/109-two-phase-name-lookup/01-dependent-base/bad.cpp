// expect: compile-error
// std: c++17
// A member of a dependent base class is not found by unqualified lookup at template definition time.
#include <cstdio>

template <class T>
struct Base {
    void hello() { std::printf("hello\n"); }
};

template <class T>
struct Derived : Base<T> {
    void run() { hello(); }                        // error: no declaration of 'hello' found at definition
};

int main() { Derived<int>{}.run(); }
