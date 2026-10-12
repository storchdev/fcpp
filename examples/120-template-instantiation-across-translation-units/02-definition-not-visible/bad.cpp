// expect: compile-error
// std: c++17
// A member template declared but never defined in this translation unit cannot be instantiated: the link fails.
#include <cstdio>

template <class T> struct Box { T get() const; T v; };   // definition lives "in the .cpp" that was not provided

int main() {
    Box<int> b{3};
    std::printf("%d\n", b.get());                  // undefined reference to Box<int>::get() const
}
